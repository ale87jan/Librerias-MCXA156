/**
 * @file    main_test_funciones_macro.c
 * @brief   Programa principal para comprobar las funciones Macro del fichero tipos.h.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "joystick.h"
#include "leds.h"

int main(void) {

  glcd_inicializar();
  
  glcd_seleccionar_fuente(FUENTE8X16);
  glcd_fondo_texto(ROJO);
  glcd_printf("COMPROBACION DE LAS MACROS INCLUIDAS EN TIPOS.H\n");
  glcd_fondo_texto(NEGRO);
  glcd_printf("DATO: %f\n", 3.4213075f);
  glcd_printf("CEIL: %d\n", CEIL(3.4213075f));
  glcd_printf("FLOOR: %d\n", FLOOR(3.4213075f));
  glcd_printf("ROUND: %f\n", ROUND(3.4213075f, 1));
  glcd_printf("FIX: %d\n", FIX(3.4213075f));
  glcd_printf("MAX(3,5): %d\n", MAX(3,5));
  glcd_printf("MIN(3,5): %d\n", MIN(3,5));
  glcd_printf("ABS(-3): %d\n", ABS(-3));
  glcd_printf("ABS(3): %d\n", ABS(3));
  glcd_printf("CONSTRAIN(8,3,5): %d\n", CONSTRAIN(8,3,5));
  glcd_printf("CONSTRAIN(-1,3,5): %d\n", CONSTRAIN(-1,3,5));
  glcd_printf("SQ(-1): %d\n", SQ(-1));
  glcd_printf("SQ(10): %d\n", SQ(10));
  glcd_printf("MAP(8,-10,10,-100,100): %d\n", MAP(8,-10,10,-100,100));
  glcd_printf("MAP(-1,-10,10,-100,100): %d\n", MAP(-1,-10,10,-100,100));
  
  while (1) {
    __WFI();
  }
}
