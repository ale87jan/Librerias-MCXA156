/**
 * @file  main_ntc.c
 * @brief Programa principal de lectura de una NTC conectada al ADC del LPC4088.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2025
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "ntc.h"

int main(void) {

  timer_inicializar(TIMER0);
  glcd_inicializar();
  adc_inicializar(1000000, ADC_CANAL_0);
  timer_iniciar_ciclos_ms(TIMER0, 10);

  while (1) {
    float32_t acumulado = 0;

    for (uint8_t i = 0; i < 100; i++) {
      uint16_t conversion = adc_convertir(ADC_CANAL_0);

      acumulado += ntc_traducir_tension_a_temperatura(adc_traducir_a_tension(conversion));

      timer_esperar_fin_ciclo(TIMER0);
    }

    glcd_xprintf(0, 24, BLANCO, NEGRO, FUENTE16X32, "Temperatura media: %3.2f", acumulado/100.0f);
  }
}
