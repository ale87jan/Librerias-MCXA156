/**
 * @file    adc_lpc40xx.c
 * @brief   Funciones de manejo del ADC del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "adc_lpc40xx.h"
#include <LPC407x_8x_177x_8x.h>
#include "error.h"

/**
 * @brief   Inicializar el ADC del LPC40xx.
 * @ingroup ADC
 *
 * @details Los pines que pueden usarse como canales de entrada para el convertidor A/D son:
 *
 *     Pin   |  Canal  | Valor del campo FUNC
 *   ------- | :-----: | :-------------------:
 *   P0[23]  |    0    |      1
 *   P0[24]  |    1    |      1
 *   P0[25]  |    2    |      1
 *   P0[26]  |    3    |      1
 *   P1[30]  |    4    |      3
 *   P1[31]  |    5    |      3
 *   P0[12]  |    6    |      3
 *   P0[13]  |    7    |      3
 *
 * La columna "Valor del campo FUNC" se refiere al valor que hay que poner en los bits FUNC del
 * registro IOCON correspondiente al pin de la primera columna para conseguir seleccionar la
 * función de entrada analógica en ese pin.
 *
 * @param[in] frecuencia_adc  Frecuencia de reloj a la que funcionará el ADC. Esta debe estar
 *                            comprendida entre 234 kHz y 12.4 MHz.
 * @param[in] canal           Indica qué canal de entrada analógico queremos usar. El pin
 *                            correspondiente al canal indicado se configurará con función
 *                            analógica. El bit seleccionado de 0 a 7 indica el canal analógico
 *                            que se utilizará.
 */
void adc_inicializar(uint32_t frecuencia_adc, adc_canal_t canal) {
  // El array puertos contiene el puerto en el que está cada pin de entrada analógico
  const uint32_t puertos[8] = {0, 0, 0, 0, 1, 1, 0, 0};

  /* El array pines contiene el número de pin dentro del puerto indicado por el array puertos
   * donde está cada pin de entrada analógico. */
  const uint32_t pines[8] = {23, 24, 25, 26, 30, 31, 12, 13};

  /* El array funciones contiene el valor del campo FUNC para seleccionar la función analógica en
   * el registro IOCON del puerto y pin de los pines con función de entrada analógica. */
  const uint32_t funciones[8] = {1, 1, 1, 1, 3, 3, 3, 3};

  uint32_t i;

  ASSERT(frecuencia_adc >= PeripheralClock / 256,
         "La frecuencia de reloj del ADC debe ser > 234 kHz.");

  ASSERT(frecuencia_adc < 12.4e6, "La frecuencia de reloj del ADC debe ser < 12.4 MHz.");

  ASSERT(canal > 0, "Selecciona al menos 1 canal. Utiliza las constantes ADC_CANAL_#.");

  // Activar el bit PCADC en el registro PCONP
  LPC_SC->PCONP |= (1u << 12);

  // Registro de CR del ADC: activar PDN, ajustar CLKDIV según frecuencia_adc, resto de bits a 0
  LPC_ADC->CR = (1u << 21) | ((PeripheralClock/frecuencia_adc - 1) << 8);

  // Configurar como entradas analógicas los pines indicados por canal
  for (i = 0; i < 8; i++) {
    if ((canal) != 0) {
      /* Si el bit i de `canal` está a 1, seleccionar la función de canal analógico i en el
       * pin adecuado.
       *
       * Obtenemos un puntero al registro IOCON que configura la función del pin en el que está el
       * canal analógico i. Los registros IOCON están colocados uno tras otro a partir de la
       * posición indicada por LPC_IOCON. Como cada puerto tiene asociado 32 registros IOCON (uno
       * por cada pin), multiplicamos el número de puerto por 32. A esto sumamos el número de pin.
       * El resultado se suma al puntero LPC_IOCON (Esta suma se hace con aritmética de punteros.
       * El compilador tiene en cuenta que cada registro IOCON ocupa 4 posicones de memoria porque
       * moldeamos el tipo del puntero LPC_IOCON a puntero a uint32_t. */
      volatile uint32_t *iocon_reg = ((uint32_t *) LPC_IOCON) + puertos[i] * 32 + pines[i];

      /* Se configura el registro IOCON del pin con el número de función adecuado para que
       * funcione como entrada analógica. */
      *iocon_reg = funciones[i];
    }
  }
}

/**
 * @brief   Realizar un conversión A/D de uno de los canales.
 * @ingroup ADC
 *
 * @param[in] canal   Canal de entrada. El bit seleccionado de 0 a 7 indica el canal analógico que
 *                    se utilizará.
 *
 * @return  Resultado de la conversión de 12 bits.
 */
uint16_t adc_convertir(adc_canal_t canal) {

  ASSERT(canal == ADC_CANAL_0 || canal == ADC_CANAL_1 || canal == ADC_CANAL_2 ||
         canal == ADC_CANAL_3 || canal == ADC_CANAL_4 || canal == ADC_CANAL_5 ||
         canal == ADC_CANAL_6 || canal == ADC_CANAL_7,
         "Canal ADC incorrecto. Utiliza las constantes ADC_CANAL_#.");

  /* Lanzar la conversión en el canal indicado activando el bit de START (solo puede estar activo el
   * canal indicado). */
  LPC_ADC->CR = (LPC_ADC->CR & ~0xFF) | (1u << 24) | canal;

  // Espera que se active el bit de DONE
  while ((LPC_ADC->GDR & (1u << 31)) == 0) {
    ;
  }

  // Devuelve el resultado de 12 bits
  return (LPC_ADC->GDR >> 4) & 0xFFF;
}

/**
 * @brief   Convierte un valor entre 0 y 4095 obtenido como resultado del convertidor A/D del
 * LPC40xx en la tensión de entrada correspondiente.
 * @ingroup ADC
 *
 * @param[in]   resultado_adc   Valor obtenido como resultado del ADC.
 *
 * @return  Tensión correspondiente a resultado_adc en Voltios.
 */
float32_t adc_traducir_a_tension(uint16_t resultado_adc) {
  // Comprobar que el valor está en el rango de los 12 bits
  ASSERT(resultado_adc < 4096u, "Valor de resultado_adc de entrada superior a 4096 (12bits).");

  // Devolver el valor convertido a voltios
  return (3.30f * (float32_t) resultado_adc) / 4096.0f;
}

/**
 * @brief   Activa en el CR los canales que se van a utilizar en el modo de ejecución por
 * hardware (mediante Timers) o modo ráfaga (Burst).
 * @ingroup ADC
 *
 * @param[in] canales   Indica qué canales de entrada analógicos queremos usar. Cada bit de 0 a 7 de
 *                      canales indica si se usará el correspondiente canal analógico.
 */
void adc_seleccionar_canales(uint8_t canales) {

  ASSERT(canales > 0, "Selecciona al menos 1 canal. Utiliza las constantes ADC_CANAL_#.");

  LPC_ADC->CR = (LPC_ADC->CR & ~0xFF) | canales;
}

/**
 * @brief   Activa en INTEN los canales que generarán una interrupción al terminar la conversión.
 * @ingroup ADC
 *
 * @param[in] canales     Indica qué canales de entrada analógicos queremos habilitar. Cada bit de
 *                        0 a 7 de canales indica si se habilitará la correspondiente interrupción.
 * @param[in] int_global  Habilita o deshabilita las interrupciones del ADC para cualquier canal.
 */
void adc_configurar_interrupciones(uint8_t canales, bool_t int_global) {
  LPC_ADC->INTEN = canales | (int_global ? ADC_INT_GLOBAL : 0);
}

/**
 * @brief   Habilita o deshabilita el modo ráfaga del ADC.
 * @ingroup ADC
 *
 * @param[in] estado  TRUE => Activar el modo ráfaga.
 */
void adc_modo_burst(bool_t estado) {

  if (estado) {
    // Borrar los bits de configuración de START y habilitar el modo ráfaga
    LPC_ADC->CR = (LPC_ADC->CR & ~(0x7 << 24)) | ADC_MODO_BURST;

  } else {
    LPC_ADC->CR &= ~ADC_MODO_BURST;
  }
}

/**
 * @brief   Configura el modo de disparo de la conversión del ADC.
 * @ingroup ADC
 *
 * @details Los diferentes valores de `modo` se recogen en la siguiente tabla:
 *
 *  Modo  | Significado
 * :----: | :----------
 *  0x0   | Detener
 *  0x1   | Iniciar conversión ahora
 *  0x2   | Iniciar conversión por flanco de P2[10]
 *  0x3   | Iniciar conversión por flanco de P1[27]
 *  0x4   | Iniciar conversión por flanco de TIMER0.MR1
 *  0x5   | Iniciar conversión por flanco de TIMER0.MR3
 *  0x6   | Iniciar conversión por flanco de TIMER1.MR0
 *  0x7   | Iniciar conversión por flanco de TIMER1.MR1
 *
 * @param[in] modo    Indica el modo de inicio de la conversión que realizará el ADC (bits START).
 * @param[in] flanco  Indica si la conversión se inicará en el flanco de subida (0) de la señal
 *                    CAP/MAT seleccionada mediante `modo` o flanco de bajada (1).
 *
 * @note  Se desactiva el modo ráfaga.
 */
void adc_modo_conversion(adc_modo_start_t modo, adc_flanco_t flanco) {

  ASSERT(modo == ADC_START_AHORA  || modo == ADC_START_P2_10  || modo == ADC_START_P1_27 ||
         modo == ADC_START_MAT0_1 || modo == ADC_START_MAT0_3 || modo == ADC_START_MAT1_0 ||
         modo == ADC_START_MAT1_1, "Modo de inicio de conversión del ADC incorrecto.");

  ASSERT(flanco == ADC_FLANCO_BAJADA || flanco == ADC_FLANCO_SUBIDA,
         "Flanco seleccionado incorrecto.");

  // Borra el modo y flanco anteriores, desactiva el modo burst y activa el modo y flanco indicados
  LPC_ADC->CR = (LPC_ADC->CR & ~(0xF << 24) & ~ADC_MODO_BURST) | modo | flanco;
}
