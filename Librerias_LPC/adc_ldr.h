/**
 * @file    adc_ldr.h
 * @brief   Conversión de la tensión en una LDR a la iluminancia en luxes correspondiente mediante
 * un divisor de tensión.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef ADC_LDR_H
#define ADC_LDR_H

#include "tipos.h"

// ===== ADC_LDR - Funciones públicas =====
float32_t adc_ldr_tension_a_iluminancia(float32_t tension);

#endif  // ADC_LDR_H
