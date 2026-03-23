/**
 * @file    piezas.h
 * @brief   Estructuras y funciones de gestion de las piezas del Tetris.
 *
 * @author      Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date        2014/2025
 * @version     2.0
 *
 * @copyright   GNU General Public License version 3 or later
 */

#ifndef PIEZAS_H
#define PIEZAS_H

#include "glcd.h"

// ===== Piezas - Constantes Públicas =====
/**
 * @brief Número de piezas diferentes.
 * @ingroup PIEZAS
 */
#define PIEZAS_NUM_PIEZAS  7

/**
 * @brief Tamaño de la matriz que se utiliza para definir las piezas.
 * @ingroup PIEZAS
 */
#define PIEZAS_TAM_MATRIZ  4

/**
 * @brief Tamaño del bloque que compone las piezas en píxeles.
 * @ingroup PIEZAS
 */
#define PIEZAS_TAM_BLOQUE  15

/**
 * @brief Constantes para representar la dirección de giro de una pieza.
 * @ingroup PIEZAS
*/
enum piezas_giro {
  DERECHA   = 0u,
  IZQUIERDA = 1u
};

// ===== Piezas - Tipos Públicos =====
/**
 * @brief   Tipo enumerado para agrupar los diferentes tipos de piezas del Tetris.
 * @ingroup PIEZAS
*/
typedef enum {
  PIEZAS_PALO,       //!< Pieza con forma de palo (1x4).
  PIEZAS_CUADRADO,   //!< Pieza con forma cuadrada (2x2).
  PIEZAS_ESE,        //!< Pieza con forma de S.
  PIEZAS_ZETA,       //!< Pieza con forma de Z.
  PIEZAS_ELE,        //!< Pieza con forma de L.
  PIEZAS_ELEREVES,   //!< Pieza con forma de L invertida.
  PIEZAS_TE          //!< Pieza con forma de T.
} piezas_tipo_t;

/**
 * @brief   Estructura para guardar la información referente a las piezas.
 * @ingroup PIEZAS
*/
typedef struct {
  piezas_tipo_t tipo; //!< Tipo de pieza.
  uint8_t tamano;     //!< Tamaño de la pieza.
  uint16_t color;     //!< Color de la pieza.
  uint8_t matriz[PIEZAS_TAM_MATRIZ][PIEZAS_TAM_MATRIZ];  //!< Matriz que define la forma de la pieza.
} piezas_t;

// ===== Piezas - Funciones Públicas =====
void piezas_inicializar(piezas_t *ptr_pieza, piezas_tipo_t tipo);
void piezas_rotar(piezas_t *ptr_pieza, uint8_t sentido);
void piezas_pintar(piezas_t *ptr_pieza, uint16_t x, uint16_t y);
void piezas_borrar(piezas_t *ptr_pieza, uint16_t x, uint16_t y);

#endif  // PIEZAS_H
