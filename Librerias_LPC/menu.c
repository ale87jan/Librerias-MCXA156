/**
 * @file    menu.c
 * @brief   Menú principal y funciones de configuración de los TIMERs para el bucle de juego y
 * detección de pulsaciones en el joystick.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "menu.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
#include "bloque.h"

// ===== Menu - Variables Globales Públicas =====
/**
 * @brief   Tiempo transcurrido en el juego.
 * @ingroup Menu
 */
uint32_t contador_ms = 0;  //!< Variable para almacenar el de juego transcurrido.

// ===== Menu - Constantes Privadas =====
/**
 * @brief   Matriz para almacenar el logo de Tetris para mostrarlo por pantalla.
 * @ingroup Menu
 */
static uint16_t rotulo[5][22] = {
  {ROJO,  ROJO, ROJO,   NEGRO, CIAN,  CIAN,     CIAN,  NEGRO,     VERDE,    VERDE,  VERDE,
   NEGRO, AZUL, AZUL,   AZUL,  NEGRO, MAGENTA,  NEGRO, AMARILLO,  AMARILLO, AMARILLO},
  {NEGRO, ROJO, NEGRO,  NEGRO, CIAN,  NEGRO,    NEGRO, NEGRO,     NEGRO,    VERDE,  NEGRO,
   NEGRO, AZUL, NEGRO,  AZUL,  NEGRO, MAGENTA,  NEGRO, AMARILLO,  NEGRO,    NEGRO },
  {NEGRO, ROJO, NEGRO,  NEGRO, CIAN,  CIAN,     CIAN,  NEGRO,     NEGRO,    VERDE,  NEGRO,
   NEGRO, AZUL, AZUL,   AZUL,  NEGRO, MAGENTA,  NEGRO, AMARILLO,  AMARILLO, AMARILLO},
  {NEGRO, ROJO, NEGRO,  NEGRO, CIAN,  NEGRO,    NEGRO, NEGRO,     NEGRO,    VERDE,  NEGRO,
   NEGRO, AZUL, AZUL,   NEGRO, NEGRO, MAGENTA,  NEGRO, NEGRO,     NEGRO,    AMARILLO},
  {NEGRO, ROJO, NEGRO,  NEGRO, CIAN,  CIAN,     CIAN,  NEGRO,     NEGRO,    VERDE,  NEGRO,
   NEGRO, AZUL, NEGRO,  AZUL,  NEGRO, MAGENTA,  NEGRO, AMARILLO,  AMARILLO, AMARILLO}
};

// ===== Menu - Variables Globales Privadas =====
/**
 * @brief   Se activa cuando se detecta una pulsación.
 * @ingroup Menu
 */
static bool_t hay_nueva_pulsacion = FALSE;

/**
 * @brief   Almacena la dirección de la nueva pulsación.
 * @ingroup Menu
 */
static uint8_t nueva_pulsacion = JOYSTICK_NADA;

/**
 * @brief   Gestiona la representación de la pantalla inicial.
 * @ingroup Menu
 */
void menu(void) {

  uint8_t i, j;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 21; j++) {
      bloque_pintar(BLOQUE_TAMANO * (5 + j), BLOQUE_TAMANO * (5 + i), rotulo[i][j]);
    }
  }

  glcd_texto(240 - 14 * 8, 200, WHITE, NEGRO, FUENTE8X16, "PULSE EL JOYSTICK PARA COMENZAR");

  do {
    leer_pulsacion();
  } while (nueva_pulsacion == JOYSTICK_NADA || nueva_pulsacion == JOYSTICK_INACTIVO);

  return;
}

/**
 * @brief   Configura el TIMER0 que se encarga del ciclo que mueve la lógica del juego.
 * @ingroup Menu
 */
void configurar_bucle_juego(void) {
  timer_inicializar(TIMER0);
  timer_iniciar_ciclos_us(TIMER0, 1000);
  NVIC_EnableIRQ(TIMER0_IRQn);

  __enable_irq();
}

/**
 * @brief   Configura el TIMER1 que se encarga del ciclo que detecta las pulsaciones del joystick.
 * @ingroup Menu
 */
void configurar_lectura_pulsaciones(void) {
  timer_inicializar(TIMER1);
  timer_iniciar_ciclos_us(TIMER1, 20000);
  NVIC_EnableIRQ(TIMER1_IRQn);

  __enable_irq();
}

/**
 * @brief   Comprueba si hay una nueva pulsación del joystick y devuelve la dirección.
 * @ingroup Menu
 *
 * @return  Dirección del joystick pulsada.
 */
uint8_t leer_pulsacion(void) {
  if (hay_nueva_pulsacion) {
    hay_nueva_pulsacion = FALSE;
    return nueva_pulsacion;
  }
  return JOYSTICK_NADA;
}

/**
 * @brief   Manejador de interrupción del TIMER0.
 * @ingroup Menu
 *
 * @details Incrementa el contador de milisegundos que se utiliza para la lógica del juego.
 */
void TIMER0_IRQHandler(void) {
  contador_ms++;
  LPC_TIMER0->IR = 1;
}

/**
 * @brief   Manejador de interrupción del TIMER1.
 * @ingroup Menu
 *
 * @details Lee el joystick y, en el caso de que se detecte una nueva pulsación activa la bandera.
 *
 * @note    No se activará de nuevo la bandera de `nueva_pulsacion` hasta que se deje de detectar
 * la última dirección pulsada.
 */
void TIMER1_IRQHandler(void) {
  static uint8_t pulsacion_anterior = 0;
  uint8_t pulsacion_actual;

  pulsacion_actual = joystick_leer();

  if (pulsacion_anterior == JOYSTICK_NADA &&
      pulsacion_actual != JOYSTICK_NADA &&
      !hay_nueva_pulsacion) {

    nueva_pulsacion = pulsacion_actual;
    hay_nueva_pulsacion = TRUE;

  } else if (pulsacion_anterior != JOYSTICK_NADA &&
            pulsacion_actual == JOYSTICK_NADA &&
            !hay_nueva_pulsacion) {

    nueva_pulsacion = JOYSTICK_INACTIVO;
    hay_nueva_pulsacion = TRUE;
  }

  pulsacion_anterior = pulsacion_actual;
  LPC_TIMER1->IR = 1;
}
