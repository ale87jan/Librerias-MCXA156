/**
 * @file    cubeta.c
 * @brief   Contiene las funciones referentes a los límites del area de juego.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "cubeta.h"
#include <stdlib.h>
#include "tipos.h"
#include "error.h"
#include "glcd.h"
#include "bloque.h"
#include "piezas.h"

/**
 * @brief   Inicializa las posiciones del área de juego.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 */
void cubeta_inicializar(cubeta_t *ptr_cubeta) {

  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");

  for (i = 0; i < CUBETA_ALTO; i++) {
    for (j = 0; j < CUBETA_ANCHO; j++) {
      ptr_cubeta->matriz[i][j] = 0;
    }
  }

  ptr_cubeta->x_pantalla = 7 * BLOQUE_TAMANO;
  ptr_cubeta->y_pantalla = 0;
}

/**
 * @brief   Dibuja el area de juego.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 */
void cubeta_pintar(cubeta_t *ptr_cubeta) {

  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");

  for (i = 0; i < CUBETA_ALTO + 1; i++) {
    bloque_pintar(ptr_cubeta->x_pantalla - BLOQUE_TAMANO,
                  ptr_cubeta->y_pantalla + i * BLOQUE_TAMANO, BLANCO);

    bloque_pintar(ptr_cubeta->x_pantalla + BLOQUE_TAMANO * CUBETA_ANCHO,
                  ptr_cubeta->y_pantalla + i * BLOQUE_TAMANO, BLANCO);
  }

  for (j = 0; j < CUBETA_ANCHO + 1; j++) {
    bloque_pintar(ptr_cubeta->x_pantalla + (j - 1) * BLOQUE_TAMANO,
                  ptr_cubeta->y_pantalla + CUBETA_ALTO * BLOQUE_TAMANO,
                  BLANCO);
  }

  for (i = 0; i < CUBETA_ALTO; i++) {
    for (j = 0; j < CUBETA_ANCHO; j++) {
      bloque_pintar(ptr_cubeta->x_pantalla + j * BLOQUE_TAMANO,
                    ptr_cubeta->y_pantalla + i * BLOQUE_TAMANO,
                    ptr_cubeta->matriz[i][j]);
    }
  }
}

/**
 * @brief   Devuelve el número de filas a eliminar por estar completas.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 *
 * @return  Número de filas eliminadas.
 */
uint8_t cubeta_revisar_filas(cubeta_t *ptr_cubeta) {

  int32_t i, j, filas_eliminadas = 0;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");

  for (i = 0; i < CUBETA_ALTO; i++) {
    for (j = 0; j < CUBETA_ANCHO; j++) {
      if (ptr_cubeta->matriz[i][j] == 0) {
        break;
      }
    }

    if (j == CUBETA_ANCHO) {
      cubeta_eliminar_fila(ptr_cubeta, i);
      filas_eliminadas++;
    }
  }
  return filas_eliminadas;
}

/**
 * @brief   Elimina la fila indicada.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] fila        Número de fila a eliminar.
 */
void cubeta_eliminar_fila(cubeta_t* ptr_cubeta, int16_t fila) {

  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(fila >= 0 && fila < CUBETA_ALTO, "Argumento fila fuera de rango");

  for (i = fila; i > 0; i--) {
    for (j = 0; j < CUBETA_ANCHO; j++) {
      ptr_cubeta->matriz[i][j] = ptr_cubeta->matriz[i - 1][j];
    }
  }

  for (j = 0; j < CUBETA_ANCHO; j++) {
    ptr_cubeta->matriz[0][j] = 0;
  }
}

/**
 * @brief   Dibuja la pieza en el área de juego.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] ptr_pieza   Ptr. a la pieza que se pintará.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 */
void cubeta_pintar_pieza(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t x, int16_t y) {

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  piezas_pintar(ptr_pieza, ptr_cubeta->x_pantalla + x * BLOQUE_TAMANO,
               ptr_cubeta->y_pantalla + y * BLOQUE_TAMANO);
}

/**
 * @brief   Borra la pieza del área de juego.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] ptr_pieza   Ptr. a la pieza que se borrará.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 */
void cubeta_borrar_pieza(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t x, int16_t y) {
  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  piezas_borrar(ptr_pieza,
               ptr_cubeta->x_pantalla + x * BLOQUE_TAMANO,
               ptr_cubeta->y_pantalla + y * BLOQUE_TAMANO);
}

/**
 * @brief   Fija la pieza al área de juego quedando como parte de esta.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] ptr_pieza   Ptr. a la pieza que se fijará.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 */
void cubeta_fijar_pieza(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t x, int16_t y) {
  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      if ((y + i) >= 0 && (y + i) < CUBETA_ALTO &&
          (x + j) >= 0 && (x + j) < CUBETA_ANCHO && ptr_pieza->matriz[i][j] != 0) {
        ptr_cubeta->matriz[y + i][x + j] = ptr_pieza->color;
      }
    }
  }
}

/**
 * @brief   Comprueba si hay interseccion entre la pieza y algún bloque existente en la cubeta.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] ptr_pieza   Ptr. a la pieza que se utilizará para verificar si hay intersección.
 * @param[in] x           Posición x de la pieza.
 * @param[in] y           Posición y de la pieza.
 *
 * @return  TRUE si hay intersección.
 */
bool_t cubeta_hay_interseccion(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t x, int16_t y) {
  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      if (ptr_pieza->matriz[i][j] != 0) {
        if ((y + i) >= CUBETA_ALTO || (x + j) >= CUBETA_ANCHO || (x + j) < 0) {
            return TRUE;
        }
        if ((y + i) >= 0 && (y + i) < CUBETA_ALTO && (x + j) >= 0 && (x + j) < CUBETA_ANCHO &&
            ptr_cubeta->matriz[y + i][x + j] != 0) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

/**
 * @brief   Comprueba si la pieza supera el límite superior del area de juego.
 * @ingroup CUBETA
 *
 * @param[in] ptr_cubeta  Ptr. a la estructura del área de juego.
 * @param[in] ptr_pieza   Ptr. a la pieza que se utilizará para verificar si hay desbordamiento.
 * @param[in] y           Posición y de la pieza.
 *
 * @return  TRUE si hay desbordamiento.
 */
bool_t cubeta_hay_desbordamiento(cubeta_t *ptr_cubeta, piezas_t *ptr_pieza, int16_t y) {

  int16_t i, j;

  ASSERT(ptr_cubeta != NULL, "El puntero ptr_cubeta es nulo");
  ASSERT(ptr_pieza != NULL, "El puntero ptr_pieza es nulo");

  for (i = 0; i < ptr_pieza->tamano; i++) {
    for (j = 0; j < ptr_pieza->tamano; j++) {
      if (ptr_pieza->matriz[i][j] != 0 && (y + i) < 0) {
        return TRUE;
      }
    }
  }
  return FALSE;
}
