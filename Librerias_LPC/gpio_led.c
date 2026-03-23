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
 * @author      Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date        2014/2025
 * @version     2.0
 *
 * @copyright   GNU General Public License version 3 or later
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

  gpio_ajustar_dir(PUERTO0, PIN13 | PIN14, DIR_SALIDA);
  gpio_ajustar_dir(PUERTO1, PIN5 | PIN18, DIR_SALIDA);

  gpio_pin_a_1(PUERTO0, PIN13 | PIN14);
  gpio_pin_a_1(PUERTO1, PIN5 | PIN18);

  /*
  LPC_GPIO0->DIR |= PIN13 | PIN14;
  LPC_GPIO1->DIR |= PIN5 | PIN18;

  LPC_GPIO0->SET = PIN13 | PIN14;
  LPC_GPIO1->SET = PIN5 | PIN18;
  */
}

/**
 * @brief   Enciende un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a encender. Debe estar entre 1 y 4.
 */
void leds_encender(uint8_t numero_led) {

  if (numero_led == LED1) {
    gpio_pin_a_0(LPC_GPIO1, PIN5);

  } else if  (numero_led == LED2) {
    gpio_pin_a_0(LPC_GPIO0, PIN14);

  } else if  (numero_led == LED3) {
    gpio_pin_a_0(LPC_GPIO0, PIN13);

  } else if  (numero_led == LED4) {
    gpio_pin_a_0(LPC_GPIO1, PIN18);

  } else {
    ERROR("Numero de LED incorrecto.");
  }

  /*
  if (numero_led == LED1) {
    LPC_GPIO1->CLR = PIN5;

  } else if  (numero_led == LED2) {
    LPC_GPIO0->CLR = PIN14;

  } else if  (numero_led == LED3) {
    LPC_GPIO0->CLR = PIN13;

  } else if  (numero_led == LED4) {
    LPC_GPIO1->CLR = PIN18;

  } else {
    ERROR("Numero de LED incorrecto.");
  }*/
}

/**
 * @brief   Apaga un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a apagar. Debe estar entre 1 y 4.
 */
void leds_apagar(uint8_t numero_led) {

  if (numero_led == LED1) {
    gpio_pin_a_1(LPC_GPIO1, PIN5);

  } else if  (numero_led == LED2) {
    gpio_pin_a_1(LPC_GPIO0, PIN14);

  } else if  (numero_led == LED3) {
    gpio_pin_a_1(LPC_GPIO0, PIN13);

  } else if  (numero_led == LED4) {
    gpio_pin_a_1(LPC_GPIO1, PIN18);

  } else {
    ERROR("Numero de LED incorrecto.");
  }

  /*
  if (numero_led == LED1) {
    LPC_GPIO1->SET = PIN5;

  } else if  (numero_led == LED2) {
    LPC_GPIO0->SET = PIN14;

  } else if  (numero_led == LED3) {
    LPC_GPIO0->SET = PIN13;

  } else if  (numero_led == LED4) {
    LPC_GPIO1->SET = PIN18;

  } else {
    ERROR("Numero de LED incorrecto.");
  }*/
}

/**
 * @brief   Invierte el estado de un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a invertir. Debe estar entre 1 y 4.
 */
void leds_invertir(uint8_t numero_led) {

  if (numero_led == LED1) {
    gpio_invertir_pin(LPC_GPIO1, PIN5);

  } else if  (numero_led == LED2) {
    gpio_invertir_pin(LPC_GPIO0, PIN14);

  } else if  (numero_led == LED3) {
    gpio_invertir_pin(LPC_GPIO0, PIN13);

  } else if  (numero_led == LED4) {
    gpio_invertir_pin(LPC_GPIO1, PIN18);

  } else {
    ERROR("Numero de LED incorrecto.");
  }

  /*
  if (numero_led == LED1) {
    LPC_GPIO1->PIN ^= PIN5;

  } else if  (numero_led == LED2) {
    LPC_GPIO0->PIN ^= PIN14;

  } else if  (numero_led == LED3) {
    LPC_GPIO0->PIN ^= PIN13;

  } else if  (numero_led == LED4) {
    LPC_GPIO1->PIN ^= PIN18;

  } else {
    ERROR("Numero de LED incorrecto.");
  }*/
}

/**
 * @brief   Ajusta el estado de un LED
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a ajustar. Debe estar entre 1 y 4.
 * @param[in]   estado      Estado que debe adoptar el LED. TRUE => encendido, FALSE => apagado.
 */
void leds_ajustar(uint8_t numero_led, bool_t estado) {
  if (estado) {
    leds_encender(numero_led);
  } else {
    leds_apagar(numero_led);
  }
}
