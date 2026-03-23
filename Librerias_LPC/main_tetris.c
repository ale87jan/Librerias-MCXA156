/**
 * @file    main_tetris.c
 * @brief   Programa principal del juego del tetris.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "error.h"
#include "timer_lpc40xx.h"
#include "leds.h"
#include "menu.h"
#include "juego.h"

int main(void) {

  glcd_inicializar();
  
  ERROR("MENSAJE DE ERROR");

  configurar_bucle_juego();
  configurar_lectura_pulsaciones();

  while (TRUE) {
    glcd_borrar(NEGRO);
    menu();
    juego();
  }
}
