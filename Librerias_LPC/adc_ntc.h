/**
 * @file    adc_ntc.h
 * @brief   Conversión de la tensión en un termistor NTC a la temperatura correspondiente mediante
 * un divisor de tensión.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef ADC_NTC_H
#define ADC_NTC_H

#include "tipos.h"

// ===== ADC_NTC - Funciones públicas =====
float32_t adc_ntc_tension_a_temperatura(float32_t V_s);

#endif  // ADC_NTC_H
