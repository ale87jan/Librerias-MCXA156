/**
 * @file    motor.c
 * @brief   Funciones de manejo del motor HSR-1425CR mediante PWM.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */
#include <LPC407x_8x_177x_8x.h>
#include "pap_a4988.h"
#include "iocon_lpc40xx.h"
#include "gpio_lpc40xx.h"

LPC_GPIO_TypeDef* motor_puerto_pin_step;
uint32_t motor_mascara_pin_step;
LPC_GPIO_TypeDef* motor_puerto_pin_dir;
uint32_t motor_mascara_pin_dir;
LPC_GPIO_TypeDef* motor_puerto_pin_enable;
uint32_t motor_mascara_pin_enable;

uint32_t motor_periodo_pwm_us = 1000000/15000;

/**
 * @brief   Inicializar la generación de señal PWM a través del pin
 *          P1[2]/ENET_TXD2/SD_CLK/PWM0[1] para gobernar el motor HSR-1425CR.
 *          El motor debe quedar en reposo.
 */
void motor_inicializar(LPC_GPIO_TypeDef* puerto_pin_enable, uint32_t mascara_pin_enable,
                       LPC_GPIO_TypeDef* puerto_pin_step, uint32_t mascara_pin_step,
                       LPC_GPIO_TypeDef* puerto_pin_dir, uint32_t mascara_pin_dir) {

  motor_puerto_pin_enable = puerto_pin_enable;
  motor_mascara_pin_enable = mascara_pin_enable;
  motor_puerto_pin_step = puerto_pin_step;
  motor_mascara_pin_step = motor_mascara_pin_step;
  motor_puerto_pin_dir = puerto_pin_dir;
  motor_mascara_pin_dir = mascara_pin_dir;

  /* Aplicar alimentación al módulo PWM0 poniendo a 1 el bit 5 de
   * LPC_SC->PCONP. */
  LPC_SC->PCONP |= 1 << 5;

  /* Configurar el pin P1[2]/ENET_TXD2/SD_CLK/PWM0[1] para que realice la
   * función PWM0[1]. */
  iocon_configurar_pin(puerto_pin_step,mascara_pin_step,PWM0_1,IOCON_NO_PULL_UP_NO_PULL_DOWN);
//  LPC_IOCON->P1_2 = 3;  //el numero 3 hace referencia a la funcion PWM0[1]
  gpio_ajustar_dir(puerto_pin_enable,mascara_pin_enable,DIR_SALIDA);
  gpio_ajustar_dir(puerto_pin_dir,mascara_pin_dir,DIR_SALIDA);
  gpio_pin_a_1(puerto_pin_enable,mascara_pin_enable);
  gpio_pin_a_1(puerto_pin_dir,mascara_pin_dir);

  /* Es mejor parar el conteo del registro TC del módulo PWM mientras se
   * realiza su configuración. Para el módulo PWM0 escribiendo 0 en su
   * registro TCR (LPC_PWM0->TCR). Esto pondrá a 0 el bit Counter Enable de
   * TCR y con ello el módulo parará (o permanecerá parado si ya lo está).*/
  LPC_PWM0->TCR = 0;

  /* Pon a 0 el registro contador de preescala, PC, y el contador principal,
   * TC. */
  LPC_PWM0->PC = 0;
  LPC_PWM0->TC = 0;

  /* Ajusta el registro de preescala, PR, para que, cuando se habilite, el
   * contador TC se incremete cada microsegundo. */
  LPC_PWM0->PR = PeripheralClock/1000000-1;

  /* Programa el registro de control de match, MCR, y el registro de match 0,
   * MR0, para que el periodo de la señal PWM sea de 20000 microsegundos
   * (20 ms). En el fichero motor.h está definido el símbolo PERIODO_PWM_US
   * con el valor 20000.
   */
  LPC_PWM0->MCR = 1 << 1;
  LPC_PWM0->MR0 = motor_periodo_pwm_us;

  /* Como usaremos la salida PWM0[1], el tiempo que la señal PWM generada
   * estará en ON estará determinada por el valor del registro de match 1,
   * MR1.
   * Queremos que el tiempo en ON inicial sea de 1545 microsegundos porque
   * así el motor estará parado inicialmente. Para conseguirlo, carga el
   * registro MR1 con el valor 1545. En el fichero motor.h está definido
   * el símbolo T_ON_REPOSO_US con el valor 1545.
   */
  LPC_PWM0->MR1 = motor_periodo_pwm_us/2;

  /* Ajusta el valor del registro PCR para habilitar la generación de
   * una señal PWM por el pin PWM0[1]. Debes configurar el modo PWM de
   * control de un solo flanco.
   */
  LPC_PWM0->PCR = 1 << 9;

  /* Pon a 1 el bit 1 del registro LER para que el registro shadow MR1 se
   * cargue con el valor de MR1 cuando se produzca el siguiente match con
   * MR0.
   */
  LPC_PWM0->LER = 1 << 1;

  // Habilita el modo PWM en el registro TCR.
  LPC_PWM0->TCR = (1 << 3);
}

/**
 * @brief       Ajustar la velocidad y sentido de giro del motor.
 *
 * @param[in]   porcentaje_velocidad    Porcentaje de la velocidad máxima del
 *                                      motor al que se quiere que gire. El
 *                                      valor debe estar entre -100 y 100. Los
 *                                      valores negativos corresponden a sentido
 *                                      de giro antihorario y los valores
 *                                      positivos a sentido de giro horario.
 */

void motor_iniciar_giro(bool_t sentido) {

  gpio_pin_a_0(motor_puerto_pin_enable,motor_mascara_pin_enable);

  gpio_escribir_pin(motor_puerto_pin_dir,motor_mascara_pin_dir,sentido);

  LPC_PWM0->TCR |= 1 ; //| (1 << 3); // Habilita el conteo

}

void motor_detener_giro(void) {

  LPC_PWM0->TCR &= ~1; // Habilita el conteo
}

void motor_bloqueo(bool_t estado) {
  gpio_escribir_pin(motor_puerto_pin_enable,motor_mascara_pin_enable,estado);
}