/**
 * @file    pwm_servo_rc.h
 * @brief   Funciones de manejo del servo de rotación contínua HSR-1425CR mediante PWM.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef PWM_SERVO_RC_H
#define PWM_SERVO_RC_H

#include "tipos.h"

// ===== PWM_SERVO_RC - Constantes Publicas =====
/**
 * @brief   Macro para evitar la zona muerta en la cual el servo no se mueve desde reposo.
 * @ingroup PWM_SERVO_RC
 */
#define PWM_SERVO_RC_EVITAR_ZONA_MUERTA FALSE

/**
 * @brief   Parámetros PWM del servo de rotación continua HSR-1425CR.
 * @ingroup PWM_SERVO_RC
 */
enum pwm_servo_rc_config {
  PWM_SERVO_RC_PERIODO_PWM_US = 20000,       //!< Periodo PWM en us.
  PWM_SERVO_RC_T_ON_REPOSO_US = 1545,        //!< Ton para reposo en us.
  PWM_SERVO_RC_ZONA_MUERTA = 10,             //!< Zona muerta desde la posición actual (deprecated).
  PWM_SERVO_RC_REPOSO_ZONA_MUERTA = 50,      //!< Zona muerta desde la posición de reposo.
  PWM_SERVO_RC_SEMIINTERVALO_T_ON_US = 180   //!< Mitad de la amplitud de variación de Ton en us.
};

// ===== PWM_SERVO_RC - Funciones Publicas =====
/**
 * @brief   Inicializa la generación de señal PWM.
 * @ingroup PWM_SERVO_RC
 *
 * @details Habilita el modulo PWM1 y configura el pin P1[18] para gobernar el servo de rotación
 * contínua HSR-1425CR. El servo debe quedar en reposo.
 */
void pwm_servo_rc_inicializar(void);

/**
 * @brief   Ajustar la velocidad y sentido de giro del servo.
 * @ingroup PWM_SERVO_RC
 *
 * @details Ajustar el tiempo en ON de la señal PWM para conseguir que el servo
 * se mueva al porcentaje de su velocidad máxima indicado por el valor absoluto
 * de velocidad y el sentido indicado por su signo. Considera que si el signo de
 * velocidad es negativo el giro debe ser antihorario y que si es positivo debe
 * ser horario.
 *
 * @param[in] porcentaje_velocidad   Velocidad de giro como porcentaje
(-100,100) de la velocidad
* máxima.
 *
 * @retval  FALSE   No se ha podido ajustar la velocidad (velocidad fuera de
 * rango).
 * @retval  TRUE    Velocidad ajustada correctamente.
 */
bool_t pwm_servo_rc_ajustar_velocidad(int8_t porcentaje_velocidad);

#endif // PWM_SERVO_RC_H
