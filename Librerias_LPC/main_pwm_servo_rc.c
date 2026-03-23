/**
 * @file    main_pwm_servo_rc.c
 * @brief   Ejemplo de manejo del servo de rotación contínua HSR-1425CR mediante PWM.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 3.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
#include "servo_pwm.h"

int main(void){

  // Inicializar el LCD y el Timer0
  glcd_inicializar();
  timer_inicializar(TIMER0);

  // Inicializar la generación PWM y dejar el motor parado
  servo_pwm_inicializar();

  while (1){
    uint8_t estado_joystick = joystick_leer();;
    static int8_t porciento_velocidad = 0;

    /* Si se pulsa el joystick hacia arriba, aumentar la velocidad si está girando en sentido
     * horario o reducirla si está girando en sentido antihorario. Esto significa, simplemente,
     * aumentar el valor de porciento_velocidad.
     * Limita el valor de porciento_velocidad a un máximo de 100.
     */
    if ((estado_joystick == JOYSTICK_ARRIBA) && (porciento_velocidad < 100)) {
      porciento_velocidad += 1;
    }

    /* Si se pulsa el joystick hacia abajo, disminuye la velocidad si está
     * girando en sentido antihorario o la reduce si está girando en sentido
     * horario. Esto significa, simplemente, disminuir el valor de
     * porciento_velocidad.
     * Limita el valor de porciento_velocidad a un mínimo de -100.
     */
    if ((estado_joystick == JOYSTICK_ABAJO) && (porciento_velocidad > -100)) {
      porciento_velocidad -= 1;
    }

    /* Muestra la velocidad en el display y realiza un retardo breve (por ejemplo 50ms) para
     * evitar que la velocidad cambie demasiado rápido.
     */
    servo_pwm_ajustar_velocidad(porciento_velocidad);
    glcd_xprintf(0,  0, BLANCO, NEGRO, FUENTE16X32, "Velocidad: %6d%%", porciento_velocidad);
    glcd_xprintf(0, 32, BLANCO, NEGRO, FUENTE16X32, "Velocidad: %6d",   LPC_PWM1->MR1);

    timer_retardo_ms(TIMER0, 50);
  }
}

