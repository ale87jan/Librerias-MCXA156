/**
 * @file    marcador.c
 * @brief   Contiene las funciones para representar la puntuación durante el juego.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <stdio.h>
#include "glcd.h"
#include "marcador.h"
#include "piezas.h"
#include "bloque.h"

/**
 * @brief   Dibuja el marcador en pantalla.
 * @ingroup Marcador
 */
void marcador_pintar(void) {

  uint8_t i;

  for (i = 0; i < 5; i++) {
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 0, BLANCO);
//  }

//  for (i = 0; i < 5; i++) {
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 6 * BLOQUE_TAMANO, BLANCO);
//  }

//  for (i = 0; i < 5; i++) {
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 9 * BLOQUE_TAMANO, BLANCO);
//  }

//  for (i = 0; i < 5; i++) {
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 12 * BLOQUE_TAMANO, BLANCO);
//  }

//  for (i = 0; i < 5; i++) {
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 15 * BLOQUE_TAMANO, BLANCO);
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 16 * BLOQUE_TAMANO, BLANCO);
    bloque_pintar(MARCADOR_X + i * BLOQUE_TAMANO, 17 * BLOQUE_TAMANO, BLANCO);
  }

  for (i = 0; i < 18; i++) {
      bloque_pintar(MARCADOR_X + BLOQUE_TAMANO * 5, i * BLOQUE_TAMANO, BLANCO);
  }

  glcd_texto(MARCADOR_X + 1, BLOQUE_TAMANO, CIAN, NEGRO, FUENTE8X16, "SIGUIENTE");
  glcd_texto(MARCADOR_X + BLOQUE_TAMANO, BLOQUE_TAMANO * 7,
             CIAN, NEGRO, FUENTE8X16, "LINEAS");
  glcd_texto(MARCADOR_X + BLOQUE_TAMANO, BLOQUE_TAMANO * 10,
             CIAN, NEGRO, FUENTE8X16, "PUNTOS");
  glcd_texto(MARCADOR_X + BLOQUE_TAMANO + BLOQUE_TAMANO / 2, BLOQUE_TAMANO * 13,
             CIAN, NEGRO, FUENTE8X16, "NIVEL");
}

/**
 * @brief   Muestra por pantalla el marcador de las lineas eliminadas.
 * @ingroup Marcador
 *
 * @param[in] lineas  Número de lineas eliminadas.
 */
void marcador_lineas(uint32_t lineas) {
  glcd_xprintf(MARCADOR_X, BLOQUE_TAMANO * 8 - 1, BLANCO, NEGRO, FUENTE8X16, "%8u", lineas);
}

/**
 * @brief   Muestra por pantalla el número de puntos alcanzado.
 * @ingroup Marcador
 *
 * @param[in] puntos  Número de puntos actual.
 */
void marcador_puntos(uint32_t puntos) {
  glcd_xprintf(MARCADOR_X, BLOQUE_TAMANO * 11 - 1, BLANCO, NEGRO, FUENTE8X16, "%8u", puntos);
}

/**
 * @brief   Muestra por pantalla el nivel actual del juego.
 * @ingroup Marcador
 *
 * @param[in] nivel
 */
void marcador_nivel(uint8_t nivel) {
  glcd_xprintf(MARCADOR_X, BLOQUE_TAMANO * 14 - 1, BLANCO, NEGRO, FUENTE8X16, "%8u", nivel);
}

/**
 * @brief   Muestra por pantalla la siguiente pieza que caerá.
 * @ingroup Marcador
 *
 * @param[in] ptr_pieza   Puntero a la pieza que se dibujará.
 */
void marcador_siguiente(piezas_t *ptr_pieza) {
  
  glcd_rectangulo_relleno(MARCADOR_X, BLOQUE_TAMANO * 2,
                          MARCADOR_X + BLOQUE_TAMANO * 5 - 1, 6 * BLOQUE_TAMANO - 1, NEGRO);
  
  piezas_pintar(ptr_pieza, MARCADOR_X + (4 - ptr_pieza->tamano) * BLOQUE_TAMANO / 2,
                BLOQUE_TAMANO * 2 + (4 - ptr_pieza->tamano) * BLOQUE_TAMANO / 2);
}