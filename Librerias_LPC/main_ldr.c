/**
 * @file  main_ldr.c
 * @brief Programa principal de lectura de una LDR conectada al ADC del LPC4088.
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
#include "ldr.h"
#include "sonido.h"

int main(void) {

  glcd_inicializar();
  adc_inicializar(1000000, ADC_CANAL_1);

  timer_inicializar(TIMER0);

  NVIC_ClearPendingIRQ(TIMER0_IRQn);
  NVIC_SetPriority(TIMER0_IRQn,0);
  NVIC_EnableIRQ(TIMER0_IRQn);

  timer_iniciar_ciclos_ms(TIMER0, 1000);

  __enable_irq();

  while (1) {
    ;
  }
}

/**
 * @brief   Rutina de servicio de interrupción del TIMER0.
 */
void TIMER0_IRQHandler(void){
  float32_t tension,iluminancia;

  tension = adc_traducir_a_tension(adc_convertir(ADC_CANAL_1));
  iluminancia = ldr_tension_a_iluminancia(tension);

  glcd_xprintf(0,  0, BLANCO, NEGRO, FUENTE16X32, "Intensidad luminosa: %9.2f", iluminancia);
  glcd_xprintf(0, 32, BLANCO, NEGRO, FUENTE16X32, "Tension: %1.3f\n", tension);

  if (iluminancia < 200) {
    sonido_emitir_pitido(1000, 100);
  }

  LPC_TIMER0->IR = 1;
}
