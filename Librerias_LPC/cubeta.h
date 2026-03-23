/**
 * @file    cubeta.h
 * @brief   Contiene las funciones referentes a los límites del area de juego.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef CUBETA_H
#define CUBETA_H

#include "error.h"
#include "piezas.h"

// ===== Cubeta - Constantes Públicas =====
/**
 * @brief   Definición del tamaño del área de juego.
 * @ingroup CUBETA
 */
enum cubeta_tamano {
  CUBETA_ALTO  = 17,  //!< Tamaño vertical del area de juego.
  CUBETA_ANCHO = 10   //!< Tamaño horizontal del area de juego.
};

// ===== Cubeta - Tipos Públicos =====
/**
 * @brief   Tipo de dato para almacenar el contenido del área de juego.
 * @ingroup CUBETA
 */
typedef struct {
  int16_t matriz[CUBETA_ALTO][CUBETA_ANCHO];  //!< Matriz para guardar el contenido de cada celda.
  int16_t x_pantalla;                         //!< Posición x del area de juego en la pantalla.
  int16_t y_pantalla;                         //!< Posición y del area de juego en la pantalla.
} cubeta_t;

// ===== Cubeta - Funciones Públicas =====
void cubeta_inicializar(cubeta_t *ptr_cubeta);

uint8_t cubeta_revisar_filas(cubeta_t *ptr_cubeta);
void cubeta_eliminar_fila(cubeta_t *ptr_cubeta, int16_t fila);;

void cubeta_pintar(cubeta_t* ptr_cubeta);
void cubeta_pintar_pieza(cubeta_t* ptr_cubeta, piezas_t* ptr_pieza, int16_t x, int16_t y);
void cubeta_borrar_pieza(cubeta_t* ptr_cubeta, piezas_t* ptr_pieza, int16_t x, int16_t y);
void cubeta_fijar_pieza(cubeta_t* ptr_cubeta, piezas_t* ptr_pieza, int16_t x, int16_t y);

bool_t cubeta_hay_interseccion(cubeta_t* ptr_cubeta, piezas_t* ptr_pieza, int16_t x, int16_t y);
bool_t cubeta_hay_desbordamiento(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t y);

#endif  // CUBETA_H
