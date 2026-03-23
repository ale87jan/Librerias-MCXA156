/**
 * @file    adc_lpc40xx.h
 * @brief   Funciones de manejo del ADC del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef ADC_LPC40XX_H
#define ADC_LPC40XX_H

#include "tipos.h"

// ===== ADC - Constantes Publicas =====
/**
 * @brief   Constantes para activar los canales del ADC en el registro CR o su interrupción en el
 * registro INTEN.
 * @ingroup ADC
 */
typedef enum {
  ADC_CANAL_0 = (1u << 0),  //!< Canal 0 del ADC
  ADC_CANAL_1 = (1u << 1),  //!< Canal 1 del ADC
  ADC_CANAL_2 = (1u << 2),  //!< Canal 2 del ADC
  ADC_CANAL_3 = (1u << 3),  //!< Canal 3 del ADC
  ADC_CANAL_4 = (1u << 4),  //!< Canal 4 del ADC
  ADC_CANAL_5 = (1u << 5),  //!< Canal 5 del ADC
  ADC_CANAL_6 = (1u << 6),  //!< Canal 6 del ADC
  ADC_CANAL_7 = (1u << 7)   //!< Canal 7 del ADC
} adc_canal_t;

/**
 * @brief   Bit del registro INTEN para habilitar las interrupciones globales de finalización de la
 * conversión del ADC.
 * @ingroup ADC
 */
#define ADC_INT_GLOBAL  (1u << 8)

/**
 * @brief   Registro CR - Constante del bit de Modo de conversión en ráfaga.
 * @ingroup ADC
 */
#define ADC_MODO_BURST  (1u << 16)

/**
 * @brief   Constantes del modo de inicio de la conversión (bits START) del registro CR.
 * @ingroup ADC
 */
typedef enum {
  ADC_STOP = (0x0 << 24),          //!< Detener la conversión del ADC.
  ADC_START_AHORA = (0x1 << 24),   //!< Modo manual: Iniciar la conversión del canal seleccionado.
  ADC_START_P2_10 = (0x2 << 24),   //!< Modo automático: Iniciar la conversión por flanco en P2[10].
  ADC_START_P1_27 = (0x3 << 24),   //!< Modo auto: Iniciar la conversión por flanco en P1[27].
  ADC_START_MAT0_1 = (0x4 << 24),  //!< Modo auto: Iniciar la conversión por match del Timer0 MR1.
  ADC_START_MAT0_3 = (0x5 << 24),  //!< Modo auto: Iniciar la conversión por match del Timer0 MR3.
  ADC_START_MAT1_0 = (0x6 << 24),  //!< Modo auto: Iniciar la conversión por match del Timer1 MR0.
  ADC_START_MAT1_1 = (0x7 << 24)   //!< Modo auto: Iniciar la conversión por match del Timer1 MR1.
} adc_modo_start_t;

/**
 * @brief   Registro CR - Constantes de flanco activo para los modos automáticos de inico de la 
 * conversión.
 * @ingroup ADC
 */
typedef enum {
  ADC_FLANCO_SUBIDA = (0u << 27),   //!< Se inicia la conversión ante un flanco de subida del pin indicado.
  ADC_FLANCO_BAJADA = (1u << 27)    //!< Se inicia la conversión ante un flanco de bajada del pin indicado.
} adc_flanco_t;

// ===== ADC - Funciones públicas =====
void adc_inicializar(uint32_t frecuencia_adc, adc_canal_t canal);
uint16_t adc_convertir(adc_canal_t canal);
float32_t adc_traducir_a_tension(uint16_t resultado_adc);

void adc_seleccionar_canales(uint8_t canales);
void adc_configurar_interrupciones(uint8_t canales, bool_t int_global);
void adc_modo_burst(bool_t estado);
void adc_modo_conversion(adc_modo_start_t modo, adc_flanco_t flanco);

#endif  // ADC_LPC40XX_H
