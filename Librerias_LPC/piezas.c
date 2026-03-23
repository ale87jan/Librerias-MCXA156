/**
 * @file    piezas.c
 * @brief   Estructuras y funciones de gestion de las piezas del Tetris.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "piezas.h"
#include "tipos.h"
#include "error.h"
#include "glcd.h"
#include "bloque.h"

// ===== Piezas - Constantes Públicas =====
/**
 * @brief   Pieza con forma de palo (1x4).
 * @ingroup Piezas
*/
piezas_t piezas_palo = {
    .tipo = PIEZAS_PALO,
    .tamano = 4,
    .color = ROJO,
    .matriz = {{0, 1, 0 ,0},
               {0, 1, 0, 0},
               {0, 1, 0, 0},
               {0, 1, 0, 0}}
};

/**
 * @brief   Pieza con forma de cuadrado (2x2).
 * @ingroup Piezas
*/
piezas_t piezas_cuadrado = {
    .tipo = PIEZAS_CUADRADO,
    .tamano = 2,
    .color = AZUL,
    .matriz = {{1, 1, 0 ,0},
               {1, 1, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}
};

/**
 * @brief   Pieza con forma de S.
 * @ingroup Piezas
*/
piezas_t piezas_ese = {
    .tipo = PIEZAS_ESE,
    .tamano = 3,
    .color = CIAN,
    .matriz = {{0, 1, 1 ,0},
               {1, 1, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}
};

/**
 * @brief   Pieza con forma de Z.
 * @ingroup Piezas
*/
piezas_t piezas_zeta = {
    .tipo = PIEZAS_ZETA,
    .tamano = 3,
    .color = MAGENTA,
    .matriz = {{1, 1, 0 ,0},
               {0, 1, 1, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}
};

/**
 * @brief   Pieza con forma de L.
 * @ingroup Piezas
*/
piezas_t piezas_ele = {
    .tipo = PIEZAS_ELE,
    .tamano = 3,
    .color = AMARILLO,
    .matriz = {{0, 1, 0 ,0},
               {0, 1, 0, 0},
               {0, 1, 1, 0},
               {0, 0, 0, 0}}
};

/**
 * @brief   Pieza con forma de L invertida.
 * @ingroup Piezas
*/
piezas_t piezas_elereves = {
    .tipo = PIEZAS_ELEREVES,
    .tamano = 3,
    .color = NARANJA,
    .matriz = {{0, 1, 0 ,0},
               {0, 1, 0, 0},
               {1, 1, 0, 0},
               {0, 0, 0, 0}}
};

/**
 * @brief   Pieza con forma de T.
 * @ingroup Piezas
*/
piezas_t piezas_te = {
    .tipo = PIEZAS_TE,
    .tamano = 3,
    .color = VERDE,
    .matriz = {{0, 1, 0 ,0},
               {1, 1, 1, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}
};


/**
 * @brief   Inicializa estructura de la pieza con el tipo indicado.
 * @ingroup Piezas
 *
 * @param[in] ptr_pieza   Puntero a la estructura de la pieza a inicializar.
 * @param[in] tipo        Tipo de la pieza.
 */
void piezas_inicializar(piezas_t *ptr_pieza, piezas_tipo_t tipo) {

  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  switch (tipo) {
    case PIEZAS_PALO:
      *ptr_pieza = piezas_palo;
      break;
    case PIEZAS_ESE:
      *ptr_pieza = piezas_ese;
      break;
    case PIEZAS_ZETA:
      *ptr_pieza = piezas_zeta;
      break;
    case PIEZAS_CUADRADO:
      *ptr_pieza = piezas_cuadrado;
      break;
    case PIEZAS_ELE:
      *ptr_pieza = piezas_ele;
      break;
    case PIEZAS_ELEREVES:
      *ptr_pieza = piezas_elereves;
      break;
    case PIEZAS_TE:
      *ptr_pieza = piezas_te;
      break;
    default:
      ERROR("Tipo de pieza incorrecto");
      break;
  }
}

/**
 * @brief   Rota 90 grados la pieza en el sentido indicado.
 * @ingroup Piezas
 *
 * @param[in] ptr_pieza   Puntero a la estructura de la pieza a girar.
 * @param[in] sentido     Sentido en el que rotar la pieza (DERECHA/IZQUIERDA).
 */
void piezas_rotar(piezas_t *ptr_pieza, uint8_t sentido) {

  uint8_t i, j, temp[PIEZAS_TAM_MATRIZ][PIEZAS_TAM_MATRIZ];

  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  if (sentido == DERECHA) {
    for (i = 0; i < ptr_pieza->tamano; i++) {
      for (j = 0; j < ptr_pieza->tamano; j++) {
        temp[j][ptr_pieza->tamano - i - 1] = ptr_pieza->matriz[i][j];
      }
    }
  } else {
    for (i = 0; i < ptr_pieza->tamano; i++) {
      for (j = 0; j < ptr_pieza->tamano; j++) {
        temp[ptr_pieza->tamano - j - 1][i] = ptr_pieza->matriz[i][j];
      }
    }
  }

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      ptr_pieza->matriz[i][j] = temp[i][j];
    }
  }
}

/**
 * @brief   Dibuja la pieza en el área de juego.
 * @ingroup Piezas
 *
 * @param[in] ptr_pieza   Puntero a la estructura de la pieza a pintar.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 */
void piezas_pintar(piezas_t *ptr_pieza, uint16_t x, uint16_t y) {

  uint8_t i, j;

  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      if (ptr_pieza->matriz[i][j] != 0) {
        bloque_pintar(x + j * PIEZAS_TAM_BLOQUE, y + i * PIEZAS_TAM_BLOQUE, ptr_pieza->color);
      }
    }
  }
}

/**
 * @brief   Borra la pieza del área de juego.
 * @ingroup Piezas
 *
 * @param[in] ptr_pieza   Puntero a la estructura de la pieza a eliminar.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 */
void piezas_borrar(piezas_t *ptr_pieza, uint16_t x, uint16_t y) {

  uint8_t i, j;

  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      if (ptr_pieza->matriz[i][j] != 0) {
          bloque_pintar(x + j * PIEZAS_TAM_BLOQUE, y + i * PIEZAS_TAM_BLOQUE, NEGRO);
      }
    }
  }
}
