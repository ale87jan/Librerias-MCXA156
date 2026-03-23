/**
 * @file    main_adc.c
 * @brief   Programa principal de uso del ADC con el potenciómetro incluido en la tarjeta Embedded 
 * Artist LPC4088.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"

int main(void) {

  timer_inicializar(TIMER0);
  glcd_inicializar();
  adc_inicializar(1000000, ADC_CANAL_2);
  timer_iniciar_ciclos_ms(TIMER0, 1000);

  while (1) {
    uint32_t conversion = adc_convertir(ADC_CANAL_2);
    float32_t tension = adc_traducir_a_tension(conversion);

    glcd_xprintf(0,  0, BLANCO, NEGRO, FUENTE16X32, "Resultado ADC: %4d\n", conversion);
    glcd_xprintf(0, 32, BLANCO, NEGRO, FUENTE16X32, "Tension pot: %1.3f\n", tension);

    timer_esperar_fin_ciclo(TIMER0);
  }
}
