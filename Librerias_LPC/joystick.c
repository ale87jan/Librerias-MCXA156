/**
 * @file    joystick.c
 * @brief   Función básica de lectura del joystick integrado en la tarjeta Embedded Artist LPC4088.
 *
 * @details Los pulsadores del joystick son activos a nivel bajo: cuando se pulsan ponen el
 * correspondiente pin del microcontrolador a 0 y cuando están sin pulsar ponen el
 * correspondiente pin a 1. Las conexiones entre el joystick el microcontrolador son:
 *
 * Pin uC | Dirección
 * ------ | ---------
 * P2[25] | ARRIBA
 * P2[27] | ABAJO
 * P2[23] | IZQUIERDA
 * P2[26] | DERECHA
 * P2[22] | CENTRAL
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "joystick.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "gpio_lpc40xx.h"
#include "leds.h"

// ===== Joystick - Funciones Publicas =====
/**
 * @brief   Leer el joystick y retornar un número diferente según la dirección que se esté pulsando.
 * @ingroup Joystick
 *
 * @retval  JOYSTICK_NADA/0 si no se está pulsando ningúna dirección.
 * @retval  JOYSTICK_ARRIBA/1 si el joystick está pulsado hacia ARRIBA.
 * @retval  JOYSTICK_ABAJO/2 si el joystick está pulsado hacia ABAJO.
 * @retval  JOYSTICK_IZQUIERDA/3 si el joystick está pulsado hacia la IZQUIERDA.
 * @retval  JOYSTICK_DERECHA/4 si el joystick está pulsado hacia la DERECHA.
 * @retval  JOYSTICK_CENTRO/5 si el joystick está pulsado hacia el CENTRO.
 */
uint8_t joystick_leer(void) {

  leds_inicializar();

  if (!gpio_leer_pin(PUERTO2, PIN23)) {
    leds_encender(LED1);
    return JOYSTICK_IZQUIERDA;
  }

  if (!gpio_leer_pin(PUERTO2, PIN25)) {

    leds_encender(LED2);
    return JOYSTICK_ARRIBA;
  }

  if (!gpio_leer_pin(PUERTO2, PIN26)) {
    leds_encender(LED3);
    return JOYSTICK_DERECHA;

  }

  if (!gpio_leer_pin(PUERTO2, PIN27)) {
    leds_encender(LED4);
    return JOYSTICK_ABAJO;
  }

  if (!gpio_leer_pin(PUERTO2, PIN22)) {
    leds_encender(LED1);
    leds_encender(LED2);
    leds_encender(LED3);
    leds_encender(LED4);
    return JOYSTICK_CENTRO;
  }

  // Todos los pines del joystick son del PUERTO2
  // uint32_t valor_puerto = PUERTO2->PIN;

  // if (!((valor_puerto >> 23) & 1)) {
    // leds_encender(LED1);
    // return JOYSTICK_IZQUIERDA;

  // } else if (!((valor_puerto >> 25) & 1)) {
    // leds_encender(LED2);
    // return JOYSTICK_ARRIBA;

  // } else if (!((valor_puerto >> 26) & 1)) {
    // leds_encender(LED3);
    // return JOYSTICK_DERECHA;

  // } else if (!((valor_puerto >> 27) & 1)) {
    // leds_encender(LED4);
    // return JOYSTICK_ABAJO;

  // } else if (!((valor_puerto >> 22) & 1)) {
    // leds_encender(LED1);
    // leds_encender(LED2);
    // leds_encender(LED3);
    // leds_encender(LED4);
    // return JOYSTICK_CENTRO;
  // }

  leds_apagar(LED1);
  leds_apagar(LED2);
  leds_apagar(LED3);
  leds_apagar(LED4);

  return JOYSTICK_NADA;
}

