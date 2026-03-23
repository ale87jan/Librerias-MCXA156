/**
 * @file    motor.h
 *
 * @brief   Funciones de manejo de un motor paso a paso mediante el drive A4988 mediante PWM para 
 * la generación de los pasos.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "tipos.h"

#define DIR_ARRIBA          1
#define DIR_ABAJO           0
#define MOTOR_BLOQUEADO     0
#define MOTOR_DESBLOQUEADO  1

void motor_inicializar(LPC_GPIO_TypeDef* puerto_pin_enable, uint32_t mascara_pin_enable,
                       LPC_GPIO_TypeDef* puerto_pin_step, uint32_t mascara_pin_step,
                       LPC_GPIO_TypeDef* puerto_pin_dir, uint32_t mascara_pin_dir);
void motor_iniciar_giro(bool_t sentido);
void motor_detener_giro(void);
void motor_bloqueo(bool_t estado);

#endif /* MOTOR_H */
