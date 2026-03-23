/**
 * @file  main_rtc.c
 * @brief Programa principal de uso del RTC.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2025
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "glcd.h"
#include "joystick.h"
#include "timer_lpc40xx.h"
#include "rtc_lpc40xx.h"
#include "sonido.h"

// Prototipos de funciones
void imprimir_reloj(fecha_hora_t fecha_hora_actual);
void imprimir_fecha(fecha_hora_t fecha_hora_actual);

void ajustar_hora_manual(fecha_hora_t *fecha_hora_actual);

int main(void) {

  fecha_hora_t fecha_hora_actual;
  
  // Inicializar periféricos
  glcd_inicializar();
  rtc_inicializar();
  timer_inicializar(TIMER0);

  // Iniciar fecha y hora comprobando si está desajustado el reloj
  if (LPC_RTC->RTC_AUX & 0x10) {
    glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE12X24, "Error, el reloj esta desajustado.");
    glcd_xprintf(0, 24, BLANCO, NEGRO, FUENTE12X24, "Ajustelo con el joystick.");
    
    timer_retardo_ms(TIMER0, 300);
    ajustar_hora_manual(&fecha_hora_actual);
    
    LPC_RTC->RTC_AUX = 0x10;
    
    // Extraer fecha con __DATE__ y sscanf con cadenas tipo "Jul 22 2024"
    char cadena_mes[4];
    uint8_t dia, mes;
    uint16_t anno;

    sscanf(__DATE__, "%s %2hhu %4hu", cadena_mes, &dia, &anno);
    
    if (cadena_mes[0] == 'F') {
      // Feb
      mes = 2;

    } else if (cadena_mes[0] == 'S') {
      // Sep
      mes = 9;

    } else if (cadena_mes[0] == 'O') {
      // Oct
      mes = 10;

    } else if (cadena_mes[0] == 'N') {
      // Nov
      mes = 11;

    } else if (cadena_mes[0] == 'D') {
      // Dec
      mes = 12;

    } else if (cadena_mes[0] == 'J' && cadena_mes[1] == 'a') {
      // Jan
      mes = 1;

    } else if (cadena_mes[0] == 'J' && cadena_mes[2] == 'n') {
      // Jun
      mes = 6;

    } else if (cadena_mes[0] == 'J' && cadena_mes[2] == 'l') {
      // Jul
      mes = 7;

    } else if (cadena_mes[0] == 'M' && cadena_mes[2] == 'r') {
      // Mar
      mes = 3;

    } else if (cadena_mes[0] == 'M' && cadena_mes[2] == 'y') {
      // May
      mes = 5;

    } else if (cadena_mes[0] == 'A' && cadena_mes[1] == 'p') {
      // Apr
      mes = 4;

    } else if (cadena_mes[0] == 'A' && cadena_mes[1] == 'u') {
      // Aug
      mes = 8;
    }
   
    fecha_hora_actual.dia_mes = dia;
    fecha_hora_actual.mes = mes;
    fecha_hora_actual.anno = anno;
    
    rtc_ajustar_fecha(fecha_hora_actual);
  }

  // Configurar interrupción RTC
  rtc_ajustar_interrupciones(RTC_INT_SEG);

  // Limpiar interrupción del ILR
  LPC_RTC->ILR = 1;

  NVIC_ClearPendingIRQ(RTC_IRQn);
  NVIC_EnableIRQ(RTC_IRQn);
  NVIC_SetPriority(RTC_IRQn, 0);

  // Habilitar globalmente las interrupciones
  __enable_irq();

  while (1) {
    ;
  }
}

/**
 * @brief   Ajustar hora del reloj manualmente.
*/
void ajustar_hora_manual(fecha_hora_t *fecha_hora_actual) {

  uint8_t horas = 0, minutos = 0, segundos = 0;

  //Ajuste actual: 0 horas, 1 minutos, 2 segundos
  uint8_t direccion = JOYSTICK_NADA, ajuste_actual = 0;

  LPC_RTC->CCR = 0;  //Detener cuenta del RTC

  do {
    fecha_hora_actual->horas = horas;
    fecha_hora_actual->minutos = minutos;
    fecha_hora_actual->segundos = segundos;

    imprimir_reloj(*fecha_hora_actual);

    switch(ajuste_actual) {
      case 0:
        glcd_xprintf(160 + 16 * 0, 100, AMARILLO, NEGRO, FUENTE16X32, "%02d", horas);
        break;
      case 1:
        glcd_xprintf(160 + 16 * 3, 100, AMARILLO, NEGRO, FUENTE16X32, "%02d", minutos);
        break;
      case 2:
        glcd_xprintf(160 + 16 * 6, 100, AMARILLO, NEGRO, FUENTE16X32, "%02d", segundos);
        break;
    }

    direccion = joystick_leer();

    if (direccion == JOYSTICK_IZQUIERDA) {
      ajuste_actual = ajuste_actual == 0 ? 0 : ajuste_actual - 1;

    }else if (direccion == JOYSTICK_DERECHA) {
      ajuste_actual = ajuste_actual == 2 ? 2 : ajuste_actual + 1;

    }else if (direccion == JOYSTICK_ARRIBA) {
      if (ajuste_actual == 0) {
        horas = horas == 23 ? 0 : horas + 1;

      }else if (ajuste_actual == 1) {
        minutos = minutos == 59 ? 0 : minutos + 1;

      }else if (ajuste_actual == 2) {
        segundos = segundos == 59 ? 0 : segundos + 1;
      }

    }else if (direccion == JOYSTICK_ABAJO) {
      if (ajuste_actual == 0) {
        horas = horas == 0 ? 23 : horas - 1;

      }else if (ajuste_actual == 1) {
        minutos = minutos == 0 ? 59 : minutos - 1;

      }else if (ajuste_actual == 2) {
        segundos = segundos == 0 ? 59 : segundos - 1;
      }
    }

    timer_retardo_ms(TIMER0, 50);

  } while (direccion != JOYSTICK_CENTRO);

  rtc_ajustar_hora(*fecha_hora_actual);

  LPC_RTC->CCR = 1;  //Iniciar cuenta del RTC

  glcd_borrar(NEGRO);
}

/**
 * @brief   Imprimir en la pantalla LCD un reloj con el formato hh:mm:ss.
 *
 * @param[in]   fecha_hora_actual   Estructura con la fecha y hora actuales.
*/
void imprimir_reloj(fecha_hora_t fecha_hora_actual) {
  glcd_xprintf(160, 100, BLANCO, NEGRO, FUENTE16X32, "%02d:%02d:%02d",
               fecha_hora_actual.horas, fecha_hora_actual.minutos, fecha_hora_actual.segundos);
}

/**
 * @brief   Imprime en la pantalla LCD la fecha en el formato DD-MM-AAAA.
 *
 * @param[in]   fecha_hora_actual   Estructura con la fecha y hora actuales.
*/
void imprimir_fecha(fecha_hora_t fecha_hora_actual) {
  glcd_xprintf(140, 40, BLANCO, NEGRO, FUENTE16X32, "%02d-%02d-%04d",
               fecha_hora_actual.dia_mes, fecha_hora_actual.mes, fecha_hora_actual.anno);
}


/**
 * @brief Manejador de interrupción del RTC.
 */
void RTC_IRQHandler(void) {

  static fecha_hora_t fecha_hora_ahora;

  rtc_leer_hora(&fecha_hora_ahora);
  rtc_leer_fecha(&fecha_hora_ahora);

  imprimir_reloj(fecha_hora_ahora);
  imprimir_fecha(fecha_hora_ahora);
  
  if (LPC_RTC->ILR & 1) {

    LPC_RTC->ILR = 1;
    
  } else if ((LPC_RTC->ILR >> 1) & 1) {
    // Lanzar alarma
    glcd_xprintf(160, 160, ROJO, AMARILLO, FUENTE16X32, "ALARMA");
    
    while (joystick_leer() != JOYSTICK_CENTRO) {
      ;
    }
    
    glcd_xprintf(160, 160, BLANCO, NEGRO, FUENTE16X32, "      ");
    
    LPC_RTC->ILR = (1u << 1);
  }
}
