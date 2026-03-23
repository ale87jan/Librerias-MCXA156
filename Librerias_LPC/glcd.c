/**
 * @file    glcd.c
 * @brief   Funciones de manejo del LCD de 4.3" desde la tarjeta Embedded Artist Developer's Kit.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "glcd.h"
#include <LPC407x_8x_177x_8x.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "tipos.h"
#include "error.h"
#include "timer_lpc40xx.h"
#include "sdram.h"
#include "fuente.h"

// Variables de las fuentes definidas en los ficheros correspondientes fuente_#
extern fuente_t fuente_8x16;
extern fuente_t fuente_12x24;
extern fuente_t fuente_16x32;

// ===== GLCD - Constantes Privadas =====
/**
 * @brief   Tabla para obtener un puntero a la fuente a partir de un número de fuente.
 * @ingroup GLCD
 * @private
 */
static fuente_t *tabla_fuentes[NUMERO_FUENTES] ={&fuente_8x16, &fuente_12x24, &fuente_16x32};

/**
 * @brief   Estructura para almacenar la configuración actual de la LCD (color, fuente y posición)
 * para la salida de texto mediante glcd_printf.
 * @ingroup GLCD
 * @private
 */
static glcd_config_texto_t texto_actual = {
  .color = BLANCO,
  .color_fondo = NEGRO,
  .fuente = FUENTE16X32,
  .pos_x = 0,
  .pos_y = 0,
  .desplazamiento_activado = TRUE
};

/**
 * @name  No Semihosting
 * @brief Reimplementación de funciones que utilizan semihosting.
 * @{
 */
FILE __stdout;
FILE __stdin;
FILE __stderr;
//!@}

/**
 * @brief   Inicializa la interfaz I2C0 como maestro.
 * @ingroup GLCD
 * @private
 *
 * @details Se utilizan los pines P0[27] como SDA y P0[28] como SCL.
 */
static void glcd_i2c0_inicializar(void) {

  // Aplicar alimentación al módulo I2C0
  LPC_SC->PCONP |= (1u << 7);

  // Funcion I2C0_SDA con IOCON_NO_PULL_UP_NO_PULL_DOWN | IOCON_FILTER | IOCON_OD
  LPC_IOCON->P0_27 = 1u | (1u << 10) | (1u << 8);

  // Funcion I2C0_SCL con IOCON_NO_PULL_UP_NO_PULL_DOWN | IOCON_FILTER | IOCON_OD
  LPC_IOCON->P0_28 = 1u | (1u << 10) | (1u << 8);

  // Limpiar los flags
  LPC_I2C0->CONCLR = (1u << 6) | (1u << 5) | (1u << 3) | (1u << 2);

  // Configurar la frecuencia del reloj SCL
  LPC_I2C0->SCLL = 300;
  LPC_I2C0->SCLH = 300;

  // Habilita la interfaz
  LPC_I2C0->CONSET = 1u << 6;
}

/**
 * @brief   Genera una condición de START en el bus I2C.
 * @ingroup GLCD
 * @private
 *
 * @retval  Valor del registro I2C0->STAT
 * @retval  -1 si se supera el timeout especificado
 */
static int8_t glcd_i2c0_start(void) {

  uint32_t contador = 0;

  // Generar la condición de START
  LPC_I2C0->CONSET = 1u << 5;

  // Esperar hasta que se transmita el START o expire el I2C0_TIMEOUT
  while ((LPC_I2C0->CONSET & (1u << 3)) == 0) {
    contador++;
    if (contador > 0x01000000) {
      return -1;
    }
  }

  LPC_I2C0->CONCLR = 1u << 5;
  return LPC_I2C0->STAT;
}

/**
 * @brief   Genera una condición de STOP en el bus I2C.
 * @ingroup GLCD
 * @private
 */
static void glcd_i2c0_stop(void) {

  LPC_I2C0->CONCLR = 1u << 3;
  LPC_I2C0->CONSET = 1u << 4;

  // Esperar hasta que se transmita el STOP
  while (LPC_I2C0->CONSET & (1u << 4)) {
    ;
  }
}

/**
 * @brief   Transmite un byte a un esclavo a través de la interfaz I2C0.
 * @ingroup GLCD
 * @private
 *
 * @param[in] dato  Byte a transmitir.
 *
 * @return  Valor del registro I2C0->STAT.
 */
static int8_t glcd_i2c0_transmitir_byte(uint8_t dato) {

  LPC_I2C0->CONCLR = 1u << 3;
  LPC_I2C0->DAT = dato;

  while ((LPC_I2C0->CONSET & (1u << 3)) == 0) {
    ;
  }

  return LPC_I2C0->STAT;
}

/**
 * @brief   Transmite un array de bytes a través del I2C0.
 * @ingroup GLCD
 * @private
 *
 * @param[in] dir_i2c   Dirección del dispositivo I2C al que transmitir los datos.
 * @param[in] buf       Ptr. al array de bytes que se enviarán.
 * @param[in] len       Longitud del array.
 */
static void glcd_i2c0_transmitir_buffer(uint8_t dir_i2c, const uint8_t *buf, uint32_t len) {

  uint32_t i;

  glcd_i2c0_start();
  glcd_i2c0_transmitir_byte(dir_i2c << 1);

  for (i = 0; i < len; i++) {
    glcd_i2c0_transmitir_byte(*buf);
    buf++;
  }

  glcd_i2c0_stop();
}

/**
 * @brief   Función de salida de caracteres que es llamada internamente desde la familia de
 * funciones printf y por tanto por glcd_printf (que usa vprintf). Reconoce los caracteres de
 * control '\\b', '\\f', '\\n', '\\r', '\\t' y '\\v'.
 * @ingroup GLCD
 * @internal
 *
 * @param[in] c       Carácter a imprimir.
 * @param[in] stream  Puntero a estructura FILE que indentifica al stream al que enviar la
 *                      salida. Sólo se reconoce stdout.
 *
 * @return  Si el fichero de salida indicado es stdout, retorna c. En caso contrario, retorna EOF.
 */
int32_t fputc(int32_t c, FILE *stream) {

  const fuente_t *fuente_ptr = tabla_fuentes[texto_actual.fuente];

  if (stream == stdout) {
    int16_t incremento_x = 0;
    uint16_t incremento_y = 0;
    switch (c) {
      case '\b':  // Backspace
        incremento_x = - fuente_ptr->pixeles_ancho;
        break;
      case '\f':  // Form feed
        texto_actual.pos_x = 0;
        incremento_y = GLCD_TAMANO_Y;
        break;
      case '\n':  // Line feed
        texto_actual.pos_x = 0;
        incremento_y = fuente_ptr->pixeles_alto;
        break;
      case '\r':  // Carriage return
        texto_actual.pos_x = 0;
        break;
      case '\t':  // Horizontal tab
        texto_actual.pos_x = ((texto_actual.pos_x / (8 * fuente_ptr->pixeles_ancho)) + 1)
                              * 8 * fuente_ptr->pixeles_ancho;
        break;
      case '\v':  // Vertical tab
        incremento_y = fuente_ptr->pixeles_alto;
        break;
      default:
        break;
    }

    if (texto_actual.pos_x < incremento_x) {
      texto_actual.pos_x = 0;
    } else if ((texto_actual.pos_x + incremento_x) > GLCD_X_MAXIMO) {
      texto_actual.pos_x = 0;
      if (incremento_y < fuente_ptr->pixeles_alto) {
        incremento_y = fuente_ptr->pixeles_alto;
      }
    } else {
      texto_actual.pos_x += incremento_x;
    }

    texto_actual.pos_y += incremento_y;
    if ((texto_actual.pos_y + fuente_ptr->pixeles_alto - 1) > GLCD_Y_MAXIMO) {
      if (texto_actual.desplazamiento_activado) {
        if (incremento_y > GLCD_TAMANO_Y) {
          incremento_y = GLCD_TAMANO_Y;
          texto_actual.pos_y = 0;
        } else if (incremento_y < GLCD_TAMANO_Y) {
          if (texto_actual.pos_y < incremento_y) {
            texto_actual.pos_y = 0;
          } else {
            texto_actual.pos_y -= incremento_y;
          }
        } else {
          texto_actual.pos_y = 0;
        }
        glcd_desplazar(incremento_y);
      } else {
        texto_actual.pos_y = 0;
      }
    }

    if (c >= fuente_ptr->primer_caracter && c <= fuente_ptr->ultimo_caracter) {
      glcd_caracter(c, texto_actual.pos_x, texto_actual.pos_y, texto_actual.color,
                    texto_actual.color_fondo, texto_actual.fuente);

      texto_actual.pos_x += fuente_ptr->pixeles_ancho;
    }
    return c;
  }

  return EOF;
}

/**
 * @brief   Función de entrada de caracteres que es llamada internamente por la familia de scanf.
 * @ingroup GLCD
 * @internal
 *
 * @param[in] file  Puntero a estructura FILE que indentifica al stream del que se quiere leer.
 *
 * @return  Siempre retorna EOF.
 *
 * @warning Función no implementada.
 */
int32_t fgetc(__attribute__((unused)) FILE *file) {
  return EOF;
}

/**
 * @brief   Comprueba el estado del indicador de error de un stream.
 * @ingroup GLCD
 * @internal
 *
 * @param[in] stream  Puntero a estructura FILE que indentifica al stream cuyo estado de error se
 *                      quiere comprobar.
 *
 * @return  Retorna un valor distinto de 0 si la operación anterior sobre el stream produjo un error
 *          y un valor igual a 0 en caso contrario. En esta implementación, si el stream es stdout
 *          siempre se retorna 0 y en caso contrario siempre se retorna un valor distinto de 0.
 */
int32_t ferror(FILE *stream) {
  if (stream == stdout) {
    return 0;
  }

  return 1;
}

/**
 * @brief   Al realizar el retarget de las funciones de la familia printf, el compilador del
 * Keil MDK precisa que se defina la función _sys_exit que corresponde a la llamada del sistema
 * `sys_exit` que termina el proceso actual. En esta implementación no se retorna al sistema (ya
 * que no hay) sino que se deja encerrado al programa en un bucle infinito.
 * @ingroup GLCD
 * @internal
 *
 * @param[in] return_code   Código que debe retornarse al sistema.
 */
void _sys_exit(__attribute__((unused)) int32_t return_code) {

  uint32_t i;

  // Dejar al programa encerrado aquí
  LPC_GPIO1->DIR |= (1u << 5);

  while (1) {
    LPC_GPIO1->CLR = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
    LPC_GPIO1->SET = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
  }
}

void glcd_inicializar(void) {

  uint32_t i, divisor_reloj;
  uint8_t buffer[5];
  bool_t sdram = FALSE;

  // Inicializa la interfaz I2C0 que se utilizará para comunicarse con el controlador del panel LCD
  glcd_i2c0_inicializar();

  /* Inicializar el controlador de SDRAM. El framebuffer se mantiene en la SDRAM conectada al
   * LPC4088 en la tarjeta de desarrollo.
   */
  sdram = sdram_inicializar();

  // Configurar la función de los pines del LPC4088 que se usan para controlar la pantalla LCD

  // LPC_IOCON->P0_4 |= 7;   // P0[4] --> LCD_VD_0
  // LPC_IOCON->P0_5 |= 7;   // P0[5] --> LCD_VD_1
  // LPC_IOCON->P0_6 |= 7;   // P0[6] --> LCD_VD_8
  // LPC_IOCON->P0_7 |= 7;   // P0[7] --> LCD_VD_9
  // LPC_IOCON->P0_8 |= 7;   // P0[8] --> LCD_VD_16
  // LPC_IOCON->P0_9 |= 7;   // P0[9] --> LCD_VD_17

  LPC_IOCON->P2_12 |= 5;  // P2[12] --> LCD_VD_3
  LPC_IOCON->P2_6 |= 7;   // P2[6]  --> LCD_VD_4
  LPC_IOCON->P0_10 |= 7;  // P0[10] --> LCD_VD_5
  LPC_IOCON->P2_8 |= 7;   // P2[8]  --> LCD_VD_6
  LPC_IOCON->P2_9 |= 7;   // P2[9]  --> LCD_VD_7

  LPC_IOCON->P1_20 |= 7;  // P1[20] --> LCD_VD_10
  LPC_IOCON->P1_21 |= 7;  // P1[21] --> LCD_VD_11
  LPC_IOCON->P1_22 |= 7;  // P1[22] --> LCD_VD_12
  LPC_IOCON->P1_23 |= 7;  // P1[23] --> LCD_VD_13
  LPC_IOCON->P1_24 |= 7;  // P1[24] --> LCD_VD_14
  LPC_IOCON->P1_25 |= 7;  // P1[25] --> LCD_VD_15

  LPC_IOCON->P2_13 |= 7;  // P2[13] --> LCD_VD_19
  LPC_IOCON->P1_26 |= 7;  // P1[26] --> LCD_VD_20
  LPC_IOCON->P1_27 |= 7;  // P1[27] --> LCD_VD_21
  LPC_IOCON->P1_28 |= 7;  // P1[28] --> LCD_VD_22
  LPC_IOCON->P1_29 |= 7;  // P1[29] --> LCD_VD_23

  LPC_IOCON->P2_0 |= 7;   // P2[0]  --> LCD_PWR
  LPC_IOCON->P2_1 |= 7;   // P2[1]  --> LCD_LE
  LPC_IOCON->P2_2 |= 7;   // P2[2]  --> LCD_DCLK
  LPC_IOCON->P2_3 |= 7;   // P2[3]  --> LCD_FP
  LPC_IOCON->P2_4 |= 7;   // P2[4]  --> LCD_ENAB_M
  LPC_IOCON->P2_5 |= 7;   // P2[5]  --> LCD_LP
  LPC_IOCON->P2_11 |= 7;  // P2[11] --> LCD_CLKIN

  // Reiniciar funciones de los pines del joystick a GPIO en vez de la External RAM
  LPC_IOCON->P2_22 = 0;
  LPC_IOCON->P2_23 = 0;
  LPC_IOCON->P2_25 = 0;
  LPC_IOCON->P2_26 = 0;
  LPC_IOCON->P2_27 = 0;

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = 0;
  buffer[2] = GLCD_PCACTRL_DISP_EN;
  buffer[3] = 0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

  buffer[0] = GLCD_PCA9532_PWM0;
  buffer[1] = 255;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

  buffer[0] = GLCD_PCA9532_PSC0;
  buffer[1] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = 0;
  buffer[2] = GLCD_PCACTRL_DISP_EN;
  buffer[3] = GLCD_LS_MODO_PWM0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = 0;
  buffer[2] = GLCD_PCACTRL_DISP_EN;
  buffer[3] = GLCD_LS_MODO_PWM0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

  timer_retardo_us(TIMER0, 100000);

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = GLCD_PCACTRL_3V3;
  buffer[2] = GLCD_PCACTRL_DISP_EN;
  buffer[3] = GLCD_LS_MODO_PWM0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

  timer_retardo_us(TIMER0, 100000);

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = GLCD_PCACTRL_3V3;
  buffer[2] = 0;
  buffer[3] = GLCD_LS_MODO_PWM0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

  timer_retardo_us(TIMER0, 100000);

  // Activar la alimentación del periférico LCD del LPC40XX
  LPC_SC->PCONP |= 1u;

  LPC_LCD->CTRL &= ~GLCD_CTRL_EN_BIT;  // Deshabilita la LCD

  LPC_LCD->TIMH = (((GLCD_PIXELES_POR_LINEA >> 4) - 1) << 2) |
                  ((GLCD_HSYNC_PULSE_WIDTH - 1) << 8) |
                  ((GLCD_HSYNC_FRONT_PORCH - 1) << 16) |
                  ((GLCD_HSYNC_BACK_PORCH - 1) << 24);

  LPC_LCD->TIMV = (GLCD_LINEAS_POR_PANEL - 1) | ((GLCD_VSYNC_PULSE_WIDTH - 1 )<< 10) |
                  (GLCD_VSYNC_FRONT_PORCH << 16) | (GLCD_VSYNC_BACK_PORCH << 24);

  // Calcular el divisor de reloj más cercano para conseguir la frecuencia deseada
  divisor_reloj = SystemCoreClock / GLCD_RELOJ_LCD;
  if (divisor_reloj >= 0x3F) {
    divisor_reloj = 0x3F;
  }

  if (divisor_reloj <= 1) {
    // Si el divisor sale inferior a 1, ignorar el divisor del reloj (GLCD_POL_BCD_BIT)
    LPC_LCD->POL = GLCD_POL_IVS_BIT | GLCD_POL_IHS_BIT | GLCD_POL_BCD_BIT |
                   ((GLCD_PIXELES_POR_LINEA - 1) << GLCD_POL_CPL);
  } else {
    divisor_reloj -= 2;
    LPC_LCD->POL = (divisor_reloj & 0x1F) | GLCD_POL_IVS_BIT | GLCD_POL_IHS_BIT |
                   ((GLCD_PIXELES_POR_LINEA - 1) << GLCD_POL_CPL) |
                   (((divisor_reloj >> 5) & 0x1F) << GLCD_POL_PCD_HI);  // 0x01DF180C
  }

  LPC_LCD->LE = 0x00000000;
  LPC_LCD->INTMSK = 0x00000000;

  LPC_LCD->CTRL = (GLCD_BPP_16 << GLCD_CTRL_BPP) | GLCD_CTRL_TFT_BIT | GLCD_CTRL_BGR_BIT;

  for (i = 0; i < 256; i++) {
    LPC_LCD->PAL[i] = 0;
  }
  LPC_SC->LCD_CFG = 0;

  LPC_LCD->CTRL |= GLCD_CTRL_EN_BIT;
  LPC_LCD->CTRL |= GLCD_CTRL_PWR_BIT;

  if (sdram) {
    LPC_LCD->UPBASE = GLCD_VRAM_BASE_ADDR & ~7UL;
    LPC_LCD->LPBASE = GLCD_VRAM_BASE_ADDR & ~7UL;
  } else {
    LPC_LCD->UPBASE = 0x10000000 & ~7UL;
    LPC_LCD->LPBASE = 0x10000000 & ~7UL;
  }

  glcd_borrar(0);

  buffer[0] = GLCD_PCA9532_PWM0;
  buffer[1] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

  buffer[0] = GLCD_PCA9532_PSC0;
  buffer[1] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

  buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
  buffer[1] = GLCD_PCACTRL_3V3;
  buffer[2] = 0;
  buffer[3] = 0;
  buffer[4] = 0;
  glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);
}

void glcd_borrar(uint16_t color) {

  uint32_t i;
  volatile uint16_t *ptr = (uint16_t *) GLCD_VRAM_BASE_ADDR;

  for (i = 0; i < GLCD_TAMANO_X * GLCD_TAMANO_Y; i++) {
    *ptr++ = color;
  }
}

void glcd_color_texto(uint16_t color) {
  texto_actual.color = color;
}

void glcd_fondo_texto(uint16_t color_fondo) {
  texto_actual.color_fondo = color_fondo;
}

void glcd_xy_texto(uint16_t x, uint16_t y) {

  if (x > GLCD_X_MAXIMO || y > GLCD_Y_MAXIMO) {
    return;
  }
  texto_actual.pos_x = x;
  texto_actual.pos_y = y;
}

void glcd_desplazar(uint16_t lineas) {

  uint32_t i;
  volatile uint16_t *ptr = (uint16_t *) GLCD_VRAM_BASE_ADDR;

  if (lineas > GLCD_TAMANO_Y) {
    lineas = GLCD_TAMANO_Y;
  }

  memmove((void *) ptr, (void *)(ptr + lineas * GLCD_TAMANO_X),
          GLCD_TAMANO_X * (GLCD_TAMANO_Y - lineas) * 2);

  ptr += GLCD_TAMANO_X * (GLCD_TAMANO_Y - lineas);
  for (i = 0; i < GLCD_TAMANO_X * lineas; i++) {
    *ptr++ = texto_actual.color_fondo;
  }
}

void glcd_activar_desplazamiento(bool_t activar) {
  texto_actual.desplazamiento_activado = activar;
}

void glcd_seleccionar_fuente(uint8_t fuente) {

  ASSERT(fuente < NUMERO_FUENTES, "Fuente incorrecta.");

  texto_actual.fuente = fuente;
}

int32_t glcd_printf(const char *format, ...) {

  int32_t retval;

  va_list args;
  va_start(args, format);
  retval = vprintf(format, args);
  va_end(args);

  return retval;
}

int32_t glcd_xprintf(uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo, uint8_t fuente,
                     const char *format, ...) {

  uint16_t pos_x_anterior, pos_y_anterior, fuente_anterior, color_anterior, color_fondo_anterior;
  int32_t retval;
  va_list args;

  pos_x_anterior = texto_actual.pos_x;
  pos_y_anterior = texto_actual.pos_y;
  color_anterior = texto_actual.color;
  color_fondo_anterior = texto_actual.color_fondo;
  fuente_anterior = texto_actual.fuente;

  texto_actual.pos_x = x;
  texto_actual.pos_y = y;
  texto_actual.color = color;
  texto_actual.color_fondo = color_fondo;
  texto_actual.fuente = fuente;

  va_start(args, format);
  retval = vprintf(format, args);
  va_end(args);

  texto_actual.pos_x = pos_x_anterior;
  texto_actual.pos_y = pos_y_anterior;
  texto_actual.color = color_anterior;
  texto_actual.color_fondo = color_fondo_anterior;
  texto_actual.fuente = fuente_anterior;

  return retval;
}

void glcd_caracter(char c, uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo,
                   uint8_t fuente) {

  const fuente_t *fuente_ptr = tabla_fuentes[fuente];
  uint16_t pixeles_ancho, pixeles_alto, bytes_por_fila, salto_en_fb, i, j;
  const uint8_t *ptr_df;
  uint8_t b, mascara;
  volatile uint16_t *ptr_fb;

  ASSERT(fuente < NUMERO_FUENTES, "Fuente incorrecta.");

  if ( x > GLCD_X_MAXIMO || y > GLCD_Y_MAXIMO) {
    return;
  }

  if (c < fuente_ptr->primer_caracter || c > fuente_ptr->ultimo_caracter) {
    return;
  }

  pixeles_ancho = fuente_ptr->pixeles_ancho;
  pixeles_alto  = fuente_ptr->pixeles_alto;
  bytes_por_fila = pixeles_ancho >> 3;
  if ((pixeles_ancho & 7) != 0) {
    bytes_por_fila++;
  }

  ptr_df = fuente_ptr->datos + (c - fuente_ptr->primer_caracter) * bytes_por_fila * pixeles_alto;

  ptr_fb = (uint16_t *) GLCD_VRAM_BASE_ADDR + y * GLCD_TAMANO_X + x;
  salto_en_fb = GLCD_TAMANO_X - fuente_ptr->pixeles_ancho;

  for (i = 0; i < pixeles_alto; i++) {
    for (j = 0; j < pixeles_ancho; j++) {
      if ((j & 7) == 0) {
        b = *ptr_df++;
        mascara = 0x80;
      } else {
        mascara >>= 1;
      }

      if (b & mascara) {
        *ptr_fb++ = color;
      } else {
        *ptr_fb++ = color_fondo;
      }
    }
    ptr_fb += salto_en_fb;
  }
}

void glcd_texto(uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo, uint8_t fuente,
                const char *str) {

  const fuente_t *fuente_ptr = tabla_fuentes[fuente];

  ASSERT(str != NULL, "El puntero a la cadena es nulo.");
  ASSERT(fuente < NUMERO_FUENTES, "Fuente incorrecta.");

  if (x > GLCD_X_MAXIMO || y > GLCD_Y_MAXIMO) {
    return;
  }

  while (*str != 0) {
    glcd_caracter(*str, x, y, color, color_fondo, fuente);

    x += fuente_ptr->pixeles_ancho;
    if (x > GLCD_X_MAXIMO) {
      x = 0;
      y += fuente_ptr->pixeles_alto;
      if (y > GLCD_Y_MAXIMO) {
        y = 0;
      }
    }
    str++;
  }
}

void glcd_punto(uint16_t x, uint16_t y, uint16_t color) {

  volatile uint16_t *ptr = (uint16_t *) GLCD_VRAM_BASE_ADDR;

  if (x > GLCD_X_MAXIMO || y > GLCD_Y_MAXIMO) {
    return;
  }

  ptr[y * GLCD_TAMANO_X + x] = color;
}

void glcd_linea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {

  uint16_t x, y;
  int32_t dx, dy, p, incE, incNE, stepx, stepy;

  // Mejorar con algoritmo Fast clipping
  dx = x1 - x0;
  dy = y1 - y0;

  if (dy < 0) {
    dy = -dy;
    stepy = -1;
  } else {
    stepy = 1;
  }

  if (dx < 0) {
    dx = -dx;
    stepx = -1;
  } else {
    stepx = 1;
  }

  x = x0;
  y = y0;
  glcd_punto(x, y, color);

  if (dx > dy) {
    p = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    while (x != x1) {
      x = x + stepx;
      if (p < 0) {
        p = p + incE;
      } else {
        y = y + stepy;
        p = p + incNE;
      }
      glcd_punto(x, y, color);
    }
  } else {
    p = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    while (y != y1) {
      y = y + stepy;
      if (p < 0) {
        p = p + incE;
      } else {
        x = x + stepx;
        p = p + incNE;
      }
      glcd_punto(x, y, color);
    }
  }
}

void glcd_rectangulo(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {

  glcd_linea(x0, y0, x1, y0, color);
  glcd_linea(x1, y0, x1, y1, color);
  glcd_linea(x1, y1, x0, y1, color);
  glcd_linea(x0, y1, x0, y0, color);
}

void glcd_rectangulo_relleno(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {

  uint16_t temp, i, j;
  uint16_t *ptr = (uint16_t *) GLCD_VRAM_BASE_ADDR;

  if (x0 > x1) {
    temp = x0;
    x0 = x1;
    x1 = temp;
  }

  if (y0 > y1) {
    temp = y0;
    y0 = y1;
    y1 = temp;
  }

  if (x1 > GLCD_X_MAXIMO) {
    x1 = GLCD_X_MAXIMO;
  }
  if (y1 > GLCD_Y_MAXIMO) {
    y1 = GLCD_Y_MAXIMO;
  }

  ptr +=  GLCD_TAMANO_X * y0 + x0;

  for (i = y0; i <= y1; i++) {
    uint16_t *ptr2 = ptr;
    ptr += GLCD_TAMANO_X;
    for (j = x0; j <= x1; j++) {
      *ptr2++ = color;
    }
  }
}

void glcd_circunferencia(uint16_t xc, uint16_t yc, uint16_t radio, uint16_t color) {

  uint16_t x = radio, y = 0;
  int32_t err = 0;

  while (x >= y) {
    glcd_punto(xc + x, yc + y, color);
    glcd_punto(xc + y, yc + x, color);
    glcd_punto(xc - y, yc + x, color);
    glcd_punto(xc - x, yc + y, color);
    glcd_punto(xc - x, yc - y, color);
    glcd_punto(xc - y, yc - x, color);
    glcd_punto(xc + y, yc - x, color);
    glcd_punto(xc + x, yc - y, color);

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    } else {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}

void glcd_circulo(uint16_t xc, uint16_t yc, uint16_t radio, uint16_t color) {

  uint16_t x = radio, y = 0;
  int32_t err = 0;

  while (x >= y) {
    glcd_linea(xc - x, yc - y, xc + x, yc - y, color);
    glcd_linea(xc - x, yc + y, xc + x, yc + y, color);
    glcd_linea(xc - y, yc - x, xc + y, yc - x, color);
    glcd_linea(xc - y, yc + x, xc + y, yc + x, color);

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    } else {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}
