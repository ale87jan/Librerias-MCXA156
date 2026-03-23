/**
 * @file    pwm_led_rgb.h
 * @brief   Funciones de manejo de un LED RGB mediante PWM.
 *
 * @details El LED RGB deberá estar conectado a los siguientes pines:
 *
 * Pin uC  | Pin placa | Pin LED    | Canal PWM
 * ------- | --------- | ---------- | ---------
 * P1[3]   | J3[29]    | R          | PWM0[2]  
 * P1[6]   | J3[30]    | G          | PWM0[4]  
 * P1[11]  | J3[31]    | B          | PWM0[6]  
 * GND     | J3[1]     | - (cátodo) |          
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef PWM_LED_RGB_H
#define PWM_LED_RGB_H

#include "tipos.h"

// ===== PWM_LED_RGB - Constantes Publicas =====
/**
 * @brief   Símbolo para la frecuencia PWM a la que se iluminará el LED.
 * @ingroup PWM_LED_RGB
 *
 * @details La frecuencia PWM para iluminación LED se recomienda superior a 100Hz para evitar que
 * el parpadeo sea visible al ojo humano. En general, cuanto mayor frecuencia mejor, aunque puede
 * dar lugar a que generen sonidos dentro del rango audible (50Hz-24kHz), y son necesarios
 * componentes de mayor calidad por la alta frecuencia de conmutación.
 *
 * Rango recomendado: 500-1000 Hz
 *
 * Frecuencia PWM = 520 Hz -> Periodo = 1923.07692us ~> 1920us -> Frecuencia final = 520.83 Hz
 *
 * @note Para evitar acoplamientos con la frecuencia de la red eléctrica (o sus armónicos) es
 * recomendable utilizar frecuencias que no sean múltiplos de 50/60Hz.
 */
#define PWM_LED_RGB_PERIODO_PWM_US  1920

/**
 * @brief   Convierte las componentes r, g y b en su homólogo de 24 bits.
 * @ingroup PWM_LED_RGB
 *
 * @details   Función para convertir el valor expresado en las componentes roja, verde y azul de
 * 8bits a 24 bits para que sea similar a como se realiza para la pantalla GLCD.
 *
 * @param[in]   r   Intensidad del led rojo
 * @param[in]   g   Intensidad del led verde
 * @param[in]   b   Intensidad del led azul
 */
#define RGB_24BITS (r, g, b) ((((r) & 0xFF) << 16) | (((g) & 0xFF) << 8) | ((b) & 0xFF))

/**
 * @brief   Simbolos de varios colores en español.
 * @ingroup PWM_LED_RGB
 */
enum led_rgb_color {
  LED_RGB_NEGRO    = RGB_24BITS(0, 0, 0),
  LED_RGB_ROJO     = RGB_24BITS(255, 0, 0),
  LED_RGB_VERDE    = RGB_24BITS(0, 255, 0),
  LED_RGB_AZUL     = RGB_24BITS(0, 0, 255),
  LED_RGB_AMARILLO = RGB_24BITS(255, 255, 0),
  LED_RGB_VIOLETA  = RGB_24BITS(255, 0, 255),
  LED_RGB_CIAN     = RGB_24BITS(0, 255, 255),
  LED_RGB_BLANCO   = RGB_24BITS(255, 255, 255)
};

// ===== PWM_LED_RGB - Funciones Publicas =====
void pwm_led_rgb_inicializar(void);
bool_t pwm_led_rgb_ajustar_color(uint32_t color);

#endif // PWM_LED_RGB_H
