/**
 * @file    juego.c
 * @brief   Contiene el algoritmo principal del bucle de juego del Tetris.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "juego.h"
#include <stdint.h>
#include <stdlib.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "bloque.h"
#include "piezas.h"
#include "cubeta.h"
#include "menu.h"
#include "marcador.h"
#include "joystick.h"

/**
 * @brief   Lógica principal del bucle de juego del Tetris.
 * @ingroup JUEGO
 */
void juego(void) {

  static piezas_t piezas_actual;
  static piezas_t piezas_siguiente;
  static cubeta_t cubeta;
  static int16_t x_piezas_actual;
  static int16_t y_piezas_actual;

  uint8_t  nivel = 1;
  uint32_t filas_completadas = 0, puntos = 0;
  uint32_t tiempo_paso = 750 - 50 * (nivel - 1);
  uint32_t temp_tiempo_paso = tiempo_paso;

  extern volatile uint32_t contador_ms;

  glcd_borrar(NEGRO);

  srand(contador_ms);

  cubeta_inicializar(&cubeta);
  cubeta_pintar(&cubeta);
  marcador_pintar();

  piezas_inicializar(&piezas_actual, (piezas_tipo_t) (rand() % PIEZAS_NUM_PIEZAS));
  x_piezas_actual = (CUBETA_ANCHO + piezas_actual.tamano - 4) / 2;
  y_piezas_actual = -piezas_actual.tamano;

  piezas_inicializar(&piezas_siguiente, (piezas_tipo_t)(rand()%PIEZAS_NUM_PIEZAS));

  cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);

  marcador_siguiente(&piezas_siguiente);
  marcador_lineas(filas_completadas);
  marcador_puntos(puntos);
  marcador_nivel(nivel);

  while (1) {
    uint8_t tecla_pulsada = leer_pulsacion();

    if (contador_ms >= tiempo_paso) {
      contador_ms = 0;

      if (cubeta_hay_interseccion(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual + 1)) {
        if (cubeta_hay_desbordamiento(&cubeta, &piezas_actual, y_piezas_actual)) {

          glcd_texto(cubeta.x_pantalla - BLOQUE_TAMANO, BLOQUE_TAMANO * 8,
                     ROJO, NEGRO, FUENTE16X32, " G A M E O V E R ");

          do {
            tecla_pulsada = leer_pulsacion();
          } while (tecla_pulsada == JOYSTICK_NADA || tecla_pulsada == JOYSTICK_INACTIVO);
          
          return;

        } else {
          uint8_t filas_eliminadas = 0;

          cubeta_fijar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
          filas_eliminadas = cubeta_revisar_filas(&cubeta);

          if (filas_eliminadas > 0) {
            cubeta_pintar(&cubeta);

            filas_completadas += filas_eliminadas;
            puntos += filas_eliminadas * 10 * nivel;

            marcador_lineas(filas_completadas);
            marcador_puntos(puntos);

            if (nivel < 9) {
              nivel = filas_completadas / 10 + 1;
              marcador_nivel(nivel);
              tiempo_paso = 750 - 50 * (nivel - 1);
            }
          }

          piezas_actual = piezas_siguiente;
          x_piezas_actual = (CUBETA_ANCHO + piezas_actual.tamano - 4) / 2;
          y_piezas_actual = -piezas_actual.tamano;

          cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);

          piezas_inicializar(&piezas_siguiente, (piezas_tipo_t) (rand() % PIEZAS_NUM_PIEZAS));
          marcador_siguiente(&piezas_siguiente);
        }
      } else {
        cubeta_borrar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
        y_piezas_actual++;
        cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
      }
    } else if (tecla_pulsada != JOYSTICK_NADA) {
      tiempo_paso = temp_tiempo_paso;

      if (tecla_pulsada == JOYSTICK_ARRIBA) {
        piezas_t piezas_temp = piezas_actual;
        piezas_rotar(&piezas_temp, DERECHA);

        if (!cubeta_hay_interseccion(&cubeta, &piezas_temp, x_piezas_actual, y_piezas_actual)) {
          cubeta_borrar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
          piezas_rotar(&piezas_actual, DERECHA);
          cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
        }

      } else if (tecla_pulsada == JOYSTICK_CENTRO) {
        piezas_t piezas_temp = piezas_actual;
        piezas_rotar(&piezas_temp, IZQUIERDA);

        if (!cubeta_hay_interseccion(&cubeta, &piezas_temp, x_piezas_actual, y_piezas_actual)) {
          cubeta_borrar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
          piezas_rotar(&piezas_actual, IZQUIERDA);
          cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
        }

      } else if (tecla_pulsada == JOYSTICK_IZQUIERDA && !cubeta_hay_interseccion(
                 &cubeta, &piezas_actual, x_piezas_actual - 1, y_piezas_actual)) {
        cubeta_borrar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
        x_piezas_actual--;
        cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);

      } else if (tecla_pulsada == JOYSTICK_DERECHA && !cubeta_hay_interseccion(
                 &cubeta, &piezas_actual, x_piezas_actual + 1, y_piezas_actual)) {
        cubeta_borrar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);
        x_piezas_actual++;
        cubeta_pintar_pieza(&cubeta, &piezas_actual, x_piezas_actual, y_piezas_actual);

      } else if (tecla_pulsada == JOYSTICK_ABAJO) {
        temp_tiempo_paso = tiempo_paso;
        tiempo_paso = 50;
      }
    }
  }
}
