/**
 * @file    leds.c
 * @brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded Artist LPC4088.
 *
 * @details Los LEDs son activos a nivel bajo: cuando uno de estos pines del microcontrolador se
 * pone a 1 el correspondiente LED se apaga y cuando se pone a 0 el LED se enciende. Las conexiones
 * entre los LEDs de la tarjeta y el microcontrolador son las siguientes:
 *
 * Pin uC | Nombre | Color
 * ------ | ------ | ------
 * P1[5]  | LED1   | ROJO
 * P0[14] | LED2   | VERDE
 * P0[13] | LED3   | VERDE
 * P1[18] | LED4   | VERDE
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "leds.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "error.h"
#include "gpio_lpc40xx.h"

/**
 * @brief   Configura como salida los pines del microcontrolador a los que están conectados a los 
 * LEDs y los apaga.
 * @ingroup LEDs
 */
void leds_inicializar(void) {
  // Ajustar GPIO como salida
  gpio_ajustar_dir(PUERTO0, PIN13 | PIN14, DIR_SALIDA);
  gpio_ajustar_dir(PUERTO1, PIN5 | PIN18, DIR_SALIDA);
  
  // Apagar LEDs (activos a nivel bajo)
  gpio_pin_a_1(PUERTO0, PIN13 | PIN14);
  gpio_pin_a_1(PUERTO1, PIN5 | PIN18);
  
  // Ajustar GPIO como salida
  // LPC_GPIO0->DIR |= (1u << 13) | (1u << 14);
  // LPC_GPIO1->DIR |= (1u << 5) | (1u << 18);

  // Apagar LEDs (activos a nivel bajo)
  // LPC_GPIO0->SET = (1u << 13) | (1u << 14);
  // LPC_GPIO1->SET = (1u << 5) | (1u << 18);
}

/**
 * @brief   Enciende un LED.
 * @ingroup LEDs
 *
 * @param[in] numero_led  Número del LED a encender. Debe estar entre 1 y 4.
 */
void leds_encender(uint8_t numero_led) {

  ASSERT(numero_led >= 1 && numero_led <= 4, "Número de LED incorrecto.");
  // Usando las funciones de acceso a los puertos

  if (numero_led == LED1) {
    gpio_pin_a_0(PUERTO1, PIN5);
    
  } else if  (numero_led == LED2) {
    gpio_pin_a_0(PUERTO0, PIN14);
    
  } else if  (numero_led == LED3) {
    gpio_pin_a_0(PUERTO0, PIN13);
    
  } else if  (numero_led == LED4) {
    gpio_pin_a_0(PUERTO1, PIN18);
    
  } else {
    ERROR("Número de LED incorrecto.");
  }

  // if (numero_led == LED1) {
    // LPC_GPIO1->CLR = (1u << 5);

  // } else if  (numero_led == LED2) {
    // LPC_GPIO0->CLR = (1u << 14);

  // } else if  (numero_led == LED3) {
    // LPC_GPIO0->CLR = (1u << 13);

  // } else if  (numero_led == LED4) {
    // LPC_GPIO1->CLR = (1u << 18);

  // } else {
    // ERROR("Numero de LED incorrecto.");
  // }
}

/**
 * @brief   Apaga un LED.
 * @ingroup LEDs
 *
 * @param[in] numero_led  Número del LED a apagar. Debe estar entre 1 y 4.
 */
void leds_apagar(uint8_t numero_led) {

  ASSERT(numero_led >= 1 && numero_led <= 4, "Número de LED incorrecto.");

  // Usando las funciones de acceso a los puertos
  if (numero_led == LED1) {
    gpio_pin_a_1(PUERTO1, PIN5);
    
  } else if  (numero_led == LED2) {
    gpio_pin_a_1(PUERTO0, PIN14);
    
  } else if  (numero_led == LED3) {
    gpio_pin_a_1(PUERTO0, PIN13);
    
  } else if  (numero_led == LED4) {
    gpio_pin_a_1(PUERTO1, PIN18);
    
  } else {
    ERROR("Número de LED incorrecto.");
  }

  // if (numero_led == LED1) {
    // LPC_GPIO1->SET = (1u << 5);

  // } else if  (numero_led == LED2) {
    // LPC_GPIO0->SET = (1u << 14);

  // } else if  (numero_led == LED3) {
    // LPC_GPIO0->SET = (1u << 13);

  // } else if  (numero_led == LED4) {
    // LPC_GPIO1->SET = (1u << 18);

  // } else {
    // ERROR("Numero de LED incorrecto.");
  // }
}

/**
 * @brief   Invierte el estado de un LED.
 * @ingroup LEDs
 *
 * @param[in] numero_led  Número del LED a invertir. Debe estar entre 1 y 4.
 */
void leds_invertir(uint8_t numero_led) {

  ASSERT(numero_led >= 1 && numero_led <= 4, "Número de LED incorrecto.");

  // Usando las funciones de acceso a los puertos

  if (numero_led == LED1) {
    gpio_invertir_pin(PUERTO1, PIN5);
    
  } else if  (numero_led == LED2) {
    gpio_invertir_pin(PUERTO0, PIN14);
    
  } else if  (numero_led == LED3) {
    gpio_invertir_pin(PUERTO0, PIN13);
    
  } else if  (numero_led == LED4) {
    gpio_invertir_pin(PUERTO1, PIN18);
    
  } else {
    ERROR("Número de LED incorrecto.");
  }

  // if (numero_led == LED1) {
    // LPC_GPIO1->PIN ^= (1u << 5);

  // } else if  (numero_led == LED2) {
    // LPC_GPIO0->PIN ^= (1u << 14);

  // } else if  (numero_led == LED3) {
    // LPC_GPIO0->PIN ^= (1u << 13);

  // } else if  (numero_led == LED4) {
    // LPC_GPIO1->PIN ^= (1u << 18);

  // } else {
    // ERROR("Numero de LED incorrecto.");
  // }
}

/**
 * @brief   Ajusta el estado de un LED.
 * @ingroup LEDs
 *
 * @param[in] numero_led  Número del LED a ajustar. Debe estar entre 1 y 4.
 * @param[in] estado      Estado que debe adoptar el LED. TRUE => encendido, FALSE => apagado.
 */
void leds_ajustar(uint8_t numero_led, bool_t estado) {

  ASSERT(numero_led >= 1 && numero_led <= 4, "Número de LED incorrecto.");
  
  if (estado) {
    leds_encender(numero_led);
  } else {
    leds_apagar(numero_led);
  }
}
