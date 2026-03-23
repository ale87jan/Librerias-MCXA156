/**
 * @file    adc_ldr.c
 * @brief   Conversión de la tensión en una LDR a la iluminancia en luxes correspondiente
 *          mediante un divisor de tensión.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 *
 * @note  El divisor de tensión se supone 3.3V - 10KOhm - PinADC - LDR - GND.
 */

#include "adc_ldr.h"
#include <math.h>

/**
 * @brief   Calcular la iluminancia en lux correspondiente a la tensión de salida del módulo
 * LDR KY-018 de Keyes.
 * @ingroup ADC_LDR
 *
 * @param[in] tension   Tensión caida en la LDR.
 *
 * @return  Iluminancia en luxes.
 *
 * @details La tensión en el PinADC es la tensión de salida del módulo sensor, que es igual a la
 * tensión en el centro del divisor de tensión formado por la resistencia fija de 10 kOhm (parte
 * superior) y la LDR (parte inferior).
 *
 * \f[
 *  tension = \frac{R_{ldr} * V_{cc}}{R_{1} + R_{ldr}} = \frac{3.3 * R_{ldr}}{10000 + R_{ldr}}
 * \f]
 *
 * Resolviendo para \f$R_{ldr}\f$
 *
 * \f[
 *  R_{ldr} = \frac{10000 * tension}{3.3 - tension}
 * \f]
 *
 * La relación entre la ilumancia (lx) y la resistencia de la LDR se toma:
 *
 * \f[
 * E_v = 1.25 * 10^7 * R_{ldr}^{-1.41}
 * \f]
 *
 * @note No hay información fiable sobre la LDR usada en el módulo KY-018 de Keyes.
 */
float32_t adc_ldr_tension_a_iluminancia(float32_t tension) {

  float32_t res_ldr;
  float32_t iluminancia;

  res_ldr = (10000.0f * tension)/(3.3f - tension);

  iluminancia = 1.25f * 1e7 * pow(res_ldr, -1.41);

  return iluminancia;
}
