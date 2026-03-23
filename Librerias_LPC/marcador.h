/**
 * @file    marcador.h
 * @brief   Contiene las funciones para representar la puntuación durante el juego.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef MARCADOR_H
#define MARCADOR_H

#include "bloque.h"
#include "piezas.h"

// ===== Marcador - Constantes Públicas =====
/**
 * @brief   Posición X del marcador.
 * @ingroup Marcador
 */
#define MARCADOR_X (18u * BLOQUE_TAMANO)

/**
 * @brief   Posición Y del marcador.
 * @ingroup Marcador
 */
#define MARCADOR_Y 0u

// ===== Marcador - Funciones Públicas =====
void marcador_pintar(void);
void marcador_puntos(uint32_t puntos);
void marcador_lineas(uint32_t lineas);
void marcador_nivel(uint8_t nivel);
void marcador_siguiente(piezas_t *ptr_pieza);

#endif  // MARCADOR_H
