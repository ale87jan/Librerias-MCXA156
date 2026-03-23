/**
 * @file    main_teclado.c
 * @brief   Programa principal para comprobación de las conexiones con un teclado matricial 4x4.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "leds.h"
#include "teclado_4x4.h"

int main(void) {

  glcd_inicializar();
  timer_inicializar(TIMER0);
//  tec4x4_inicializar(TEC4X4_CONEX_ABAJO);
  tec4x4_inicializar(TEC4X4_CONEX_ARRIBA);

  while (1) {
    char umbral[200];

    glcd_xprintf(0,0,BLANCO,NEGRO,FUENTE16X32,"Test de teclado\n");

    glcd_xy_texto(0,32);
    tec4x4_leer_cadena(umbral, 200);

    glcd_borrar(NEGRO);
  }
}
