/**
 * @file    bloque.h
 * @brief   Contiene las funciones de dibujado de los bloques.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef BLOQUE_H
#define BLOQUE_H

#include "tipos.h"

// ===== Bloque - Constantes Públicas =====
/**
 * @brief   Constante que contiene un patrón para que los bloques no sean de color uniforme y
 * parezcan tridimensionales.
 * @ingroup BLOQUE
 */
#define BLOQUE_TAMANO 15u

// ===== Bloque - Funciones Públicas =====
void bloque_pintar(uint16_t x, uint16_t y, uint16_t color);

#endif  // BLOQUE_H
