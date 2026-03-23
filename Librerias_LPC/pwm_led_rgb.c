/**
 * @file    pwm_led_rgb.c
 * @brief   Funciones de manejo de un LED RGB mediante PWM.
 *
 * @details  El LED RGB deberá estar conectado a los siguientes pines:
 *
 * Pin uC   | Canal PWM | Pin placa
 * -------- | -------   | ---------
 * P1[3]    | PWM0[2]   | J3[29]
 * P1[6]    | PWM0[4]   | J3[30]
 * P1[11]   | PWM0[6]   | J3[31]
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "pwm_led_rgb.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "iocon_lpc40xx.h"

/**
 * @brief   Inicializa el LED RGB.
 * @ingroup PWM_LED_RGB
 *
 * @details Esta función realiza la configuración necesaria para controlar un LED RGB mediante
 * PWM utilizando el módulo PWM0.
 */
void pwm_led_rgb_inicializar(void) {

  // Aplicar alimentación al módulo PWM0 poniendo a 1 el bit 5 de LPC_SC->PCONP
  LPC_SC->PCONP |= (1u << 5);

  // Configurar los pines para realizar las funciones PWM0[2], PWM0[4] y PWM0[6]
  iocon_configurar_pin(PUERTO1, PIN3, PWM0_2, 0);
  iocon_configurar_pin(PUERTO1, PIN6, PWM0_4, 0);
  iocon_configurar_pin(PUERTO1, PIN11, PWM0_6, 0);

  /* Es mejor parar el conteo del registro TC del módulo PWM mientras se realiza su configuración.
   * Para el módulo PWM0 escribiendo 0 en su registro TCR. Esto pondrá a 0 el bit Counter Enable
   * del TCR y la cuenta del módulo se dentendrá (o permanecerá detenida si ya lo estaba). */
  LPC_PWM0->TCR = 0;

  // Pon a 0 el registro contador de preescala, PC, y el contador principal, TC
  LPC_PWM0->PC = 0;
  LPC_PWM0->TC = 0;

  // Ajusta el registro de preescala, PR, para que el contador TC se incremete cada microsegundo
  LPC_PWM0->PR = PeripheralClock * 1E-6 - 1;

  /* Programa el registro de control de match, MCR, y el registro de match 0, MR0, para que el
   * periodo de la señal PWM sea de 1920 us. En el fichero led_rgb.h está definida la constante
   * PWM_LED_RGB_PERIODO_PWM_US con el valor correspondiente. */
  LPC_PWM0->MCR = (1u << 1);
  LPC_PWM0->MR0 = PWM_LED_RGB_PERIODO_PWM_US;

  /* Los tres LEDs deben estar apagados inicialmente así que carga los registros de match MR2, MR4
   * y MR6 se cargan con el valor 0 inicialmente. */
  LPC_PWM0->MR2 = 0;
  LPC_PWM0->MR4 = 0;
  LPC_PWM0->MR6 = 0;

  /* Ajusta el valor del registro PCR del módulo PWM para habilitar la generación de señales PWM por
   * los canales 2, 4 y 6 del módulo. Debes configurar el modo PWM de control de un solo flanco. */
  LPC_PWM0->PCR = (1u << 10) | (1u << 12) | (1u << 14);

  /* Pon a 1 los bits 2, 4 y 6 del registro LER para que cuando se produzca el siguiente match con
   * MR0, los registros shadow correspondientes se carguen con los nuevos valores. */
  LPC_PWM0->LER = (1u << 2) | (1u << 4) | (1u << 6);

  // Habilita el conteo y el modo PWM en el registro TCR
  LPC_PWM0->TCR = (1u << 0) | (1u << 3);
}

/**
 * @brief   Ajustar el color del LED RGB.
 * @ingroup PWM_LED_RGB
 *
 * @details Ajustar los registros correspondientes para ajustar la intensidad de cada color.
 *
 * Por ejemplo, si el valor de rojo es 0 el registro correspondiente debe cargarse con 0 para que
 * el ciclo de trabajo sea del 0% y LED rojo esté apagado todo el tiempo mientras que si es 255 el
 * registro debe cargarse con el valor LED_RGB_PERIODO_PWM_US para que el ciclo de trabajo sea del
 * 100% y el LED rojo esté encendido todo el tiempo.
 *
 * @param[in]   color   Color expresado en la forma de 24bits (8r:8g:8b).
 *
 * @retval  TRUE    Color ajustado correctamente.
 * @retval  FALSE   No se ha podido ajustar el color por estar fuera de rango.
 */
bool_t pwm_led_rgb_ajustar_color(uint32_t color) {

  uint8_t r, g, b;

  // Comprobar que los 8bits más significativos deben estar a 0 o retornar FALSE
  if ((color >> 24) != 0) {
    return FALSE;
  }
  // Descomponer el color en sus componentes r, g y b teniendo en cuenta que el formato es 8r:8g:8b
  r = (color >> 16)& 0xFF;
  g = (color >> 8) & 0xFF;
  b = color & 0xFF;

  // Ajustar los registros MR2, MR4 y MR6 para ajustar la intensidad de cada color
  LPC_PWM0->MR2 = (r * PWM_LED_RGB_PERIODO_PWM_US) / 255;
  LPC_PWM0->MR4 = (g * PWM_LED_RGB_PERIODO_PWM_US) / 255;
  LPC_PWM0->MR6 = (b * PWM_LED_RGB_PERIODO_PWM_US) / 255;

  /* Pon a 1 los bits 2, 4 y 6 del registro LER para que cuando se produzca el siguiente match con
   * MR0, los registros shadow correspondientes se carguen con los nuevos valores. */
  LPC_PWM0->LER = (1u << 2) | (1u << 4) | (1u << 6);

  return TRUE;
}
