/**
 * @file    pwm_servo_rc.c
 * @brief   Funciones de manejo del servo de rotación contínua HSR-1425CR mediante PWM.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "pwm_servo_rc.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "iocon_lpc40xx.h"

// ===== PWM_SERVO_RC - Funciones Publicas =====
void pwm_servo_rc_inicializar(void) {

  // Aplicar alimentación al módulo PWM1 poniendo a 1 el bit 6 de LPC_SC->PCONP
  LPC_SC->PCONP |= (1u << 6);

  // Configurar el pin P1[18] para que realice la función PWM1[1]
  iocon_configurar_pin(PUERTO1, PIN18, PWM1_1, 0);

  /* Es mejor parar el conteo del registro TC del módulo PWM mientras se realiza su configuración.
   * Para el módulo PWM1 escribiendo 0 en su registro TCR (LPC_PWM1->TCR). Esto pondrá a 0 el bit
   * Counter Enable de TCR y con ello el módulo parará (o permanecerá parado si ya lo está).
   */
  LPC_PWM1->TCR = 0;

  // Poner a 0 el registro contador de preescala, PC, y el contador principal, TC
  LPC_PWM1->PC = 0;
  LPC_PWM1->TC = 0;

  // Ajusta el registro de preescala, PR, para que el contador TC se incremente cada microsegundo
  LPC_PWM1->PR = PeripheralClock * 1e-6 - 1;

  /* Programa el registro de control de match, MCR, y el registro de match 0, MR0, para que el
   * periodo de la señal PWM sea de 20000 microsegundos (20 ms). En el fichero servo_pwm.h está
   * definido el símbolo PWM_SERVO_RC_PERIODO_PWM_US con el valor 20000.
   */
  LPC_PWM1->MCR = (1u << 1);
  LPC_PWM1->MR0 = PWM_SERVO_RC_PERIODO_PWM_US - 1;

  /* Como usaremos la salida PWM1[1], el tiempo que la señal PWM generada estará en ON estará
   * determinada por el valor del registro de match 1, MR1.
   * Queremos que el tiempo en ON inicial sea de 1545 microsegundos porque así el servo estará
   * parado inicialmente. Para conseguirlo, carga el registro MR1 con el valor 1545. En el fichero
   * servo_pwm.h está definido el símbolo PWM_SERVO_RC_T_ON_REPOSO_US con dicho valor.
   */
  LPC_PWM1->MR1 = PWM_SERVO_RC_T_ON_REPOSO_US;

  /* Ajustar el valor del registro PCR para habilitar la generación de una señal PWM por el pin
   * PWM1[1]. Configurar el modo PWM de control de un solo flanco.
   */
  LPC_PWM1->PCR = (1u << 9);

  /* Poner a 1 el bit 1 del registro LER para que el registro shadow MR1 se cargue con el valor
   * de MR1 cuando se produzca el siguiente match con MR0.
   */
  LPC_PWM1->LER = (1u << 1);

  // Habilita el conteo y el modo PWM en el registro TCR
  LPC_PWM1->TCR = (1u << 0) | (1u << 3);
}

bool_t pwm_servo_rc_ajustar_velocidad(int8_t velocidad) {

  // Si el valor de velocidad es menor que -100 o mayor que 100, retornar FALSE inmediatamente.
  if (velocidad > 100 || velocidad < -100) {
    return FALSE;
  }

  int32_t incremento_us = (PWM_SERVO_RC_SEMIINTERVALO_T_ON_US * velocidad) / 100;
  
#if PWM_SERVO_RC_EVITAR_ZONA_MUERTA
  if ((incremento_us < PWM_SERVO_RC_REPOSO_ZONA_MUERTA / 2) && (velocidad > 0)) {
    incremento_us += PWM_SERVO_RC_REPOSO_ZONA_MUERTA / 2;

  } else if ((incremento_us > -PWM_SERVO_RC_REPOSO_ZONA_MUERTA / 2) && (velocidad < 0)) {
    incremento_us -= PWM_SERVO_RC_REPOSO_ZONA_MUERTA / 2;
  }
#endif

  /* Ajustar el registro MR1 para que el tiempo en ON de la señal PWM sea el adecuado para
   * conseguir que el servo se mueva al porcentaje de su velocidad máxima indicado por el valor
   * absoluto de velocidad y el sentido indicado por su signo. Consejo: Utiliza las constantes
   * PWM_SERVO_RC_T_ON_REPOSO_US y PWM_SERVO_RC_SEMIINTERVALO_T_ON_US. */
  LPC_PWM1->MR1 = PWM_SERVO_RC_T_ON_REPOSO_US + incremento_us;

  /* Escribe en el registro LER el valor adecuado para que el registro shadow MR1 se actualice
   * con el valor del registro MR1 cuando ocurra el siguiente evento de match con MR0. */
  LPC_PWM1->LER = (1u << 1);

  return TRUE;
}

