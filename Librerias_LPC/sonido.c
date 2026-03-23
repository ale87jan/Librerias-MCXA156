/**
 * @file    sonido.c
 * @brief   Funciones básicas de sonido.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "sonido.h"
#include <LPC407x_8x_177x_8x.h>
#include <stdlib.h>
#include "error.h"
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"

/**
 * @{
 * @name    Variables globales de reproducción de una melodía.
 * @details Variables globales para representar el estado de la reproducción de una melodía.
 */
static sonido_melodia_t *g_ptr_melodia;
static volatile bool_t   g_reproduciendo = FALSE;
static volatile uint32_t g_semiperiodos_nota_actual = 1;
static volatile uint32_t g_semiperiodo_actual = 0;
static volatile uint16_t g_nota_actual = 0;
static volatile uint16_t g_duracion_us_notas = 0;
//!@}


/**
 * @brief   Generar un pitido a través del altavoz.
 * @ingroup Sonido
 *
 * @param[in] frecuencia    Frecuencia del pitido.
 * @param[in] duracion_ms   Duración del pitido en milisegundos.
 *
 * @warning No llamar a la función inicializar o se bloqueará la ejecución del programa.
 */
void sonido_emitir_pitido(uint32_t frecuencia, uint32_t duracion_ms) {

  uint32_t T_2_us = 500000 / frecuencia;
  uint32_t N_periodos = duracion_ms * frecuencia / 1000;
  uint32_t i;

  gpio_ajustar_dir(PUERTO0, PIN26, DIR_SALIDA);

  timer_inicializar(SONIDO_TIMER);
  timer_iniciar_ciclos_us(SONIDO_TIMER, T_2_us);

  for (i = 0; i < N_periodos; i++) {
    gpio_pin_a_1(PUERTO0, PIN26);
    timer_esperar_fin_ciclo(SONIDO_TIMER);
    gpio_pin_a_0(PUERTO0, PIN26);
    timer_esperar_fin_ciclo(SONIDO_TIMER);
  }
}

/**
 * @brief   Inicializar el sistema de reproducción de sonidos.
 * @ingroup Sonido
 */
void sonido_inicializar(void) {

  gpio_ajustar_dir(PUERTO0, PIN26, DIR_SALIDA);

  timer_inicializar(SONIDO_TIMER);
  SONIDO_TIMER->TCR = 0;
  SONIDO_TIMER->TC = 0;
  SONIDO_TIMER->PC = 0;
  SONIDO_TIMER->PR = PeripheralClock * 1e-6 - 1;  // Preescala para us
  SONIDO_TIMER->IR = 1;
  SONIDO_TIMER->MR0 = 1;
  SONIDO_TIMER->MCR = (1u << 1) | (1u << 0);  // Reset e Interrupcion con MR0

  NVIC_ClearPendingIRQ(SONIDO_TIMER_IRQn);
  NVIC_SetPriority(SONIDO_TIMER_IRQn, 0);
  NVIC_EnableIRQ(SONIDO_TIMER_IRQn);

  __enable_irq();
}

/**
 * @brief   Hacer sonar una nota a través del altavoz.
 * @ingroup Sonido
 *
 * @param[in] nota          Nota musical según las definiciones en sonido.h.
 * @param[in] duracion_ms   Duración de la nota en milisegundos.
 *
 * @pre Se ha de haber inicializado con anterioridad la librería.
 */
void sonido_reproducir_nota(uint8_t nota, uint32_t duracion_ms) {
  uint32_t T_2_us;
  uint32_t N_periodos;
  uint32_t i;

  if (nota == 0) {
    timer_retardo_ms(SONIDO_TIMER, duracion_ms);
    return;
  }

  T_2_us = kNotaASemiperiodoUs[nota];
  N_periodos = 1000 * duracion_ms / (2 * T_2_us);

  gpio_ajustar_dir(PUERTO0, PIN26, DIR_SALIDA);

  timer_iniciar_ciclos_us(SONIDO_TIMER, T_2_us);

  for (i = 0; i < N_periodos; i++) {
    gpio_pin_a_1(PUERTO0, PIN26);
    timer_esperar_fin_ciclo(SONIDO_TIMER);
    gpio_pin_a_0(PUERTO0, PIN26);
    timer_esperar_fin_ciclo(SONIDO_TIMER);
  }
}

/**
 * @brief   Reproducir una melodía y esperar que finalice.
 * @ingroup Sonido
 *
 * @param[in] notas         Ptr. a la melodía que termina con SONIDO_NOTA_FIN.
 * @param[in] duracion_ms   Duración de la nota en milisegundos.
 *
 * @pre   Se ha de haber inicializado con anterioridad la librería.
 */
void sonido_reproducir_melodia(const uint8_t *ptr_notas, uint32_t duracion_nota_ms) {

  ASSERT(ptr_notas != NULL, "Puntero a melodia nulo.");

  while (*ptr_notas != SONIDO_NOTA_FIN) {
    sonido_reproducir_nota(*ptr_notas, duracion_nota_ms);
    ptr_notas++;
  }
}

/**
 * @brief   Iniciar la reproducción de una melodía a través del altavoz.
 * @ingroup Sonido
 *
 * @param[in] ptr_melodia   Ptr. a la melodía que termina con SONIDO_NOTA_FIN.
 */
void sonido_iniciar_melodia(sonido_melodia_t *ptr_melodia) {

  uint16_t T_2_nota_us;
  uint32_t duracion_us_nota_actual;
  int8_t tipo_nota;

  ASSERT(ptr_melodia->ptr_notas != NULL, "Puntero a melodia nulo.");
  ASSERT(ptr_melodia->ptr_notas[0] != SONIDO_NOTA_FIN, "Melodía inicia con Nota final");

  g_reproduciendo = TRUE;

  g_ptr_melodia = ptr_melodia;
  g_nota_actual = 0;

  T_2_nota_us = 1E6 / (2 * ptr_melodia->ptr_notas[g_nota_actual]);
  g_duracion_us_notas = (60E6 * 4) / ptr_melodia->tempo;
  tipo_nota = ptr_melodia->ptr_duracion_nota[g_nota_actual];
  duracion_us_nota_actual = ((tipo_nota > 0 ? 1 : 1.5) * g_duracion_us_notas) / abs(tipo_nota);
  g_semiperiodos_nota_actual = duracion_us_nota_actual / T_2_nota_us;

  gpio_pin_a_1(PUERTO0, PIN26);

  SONIDO_TIMER->MR0 = T_2_nota_us;
  SONIDO_TIMER->TC = 0;
  SONIDO_TIMER->TCR = 1;
}

/**
 * @brief   Informar si se está reproduciendo una melodía en este momento.
 *
 * @retval  TRUE => sí se esta reproduciendo.
 * @retval  FALSE => no se está reproduciendo.
 */
bool_t sonido_reproduciendo(void) {
  return g_reproduciendo;
}

/**
 * @brief   Función manejadora de las interrupciones del TIMER configurado como SONIDO_TIMER.
 */
void SONIDO_TIMER_IRQHandler(void) {

  uint8_t siguiente_nota;
  int8_t tipo_nota;

  g_semiperiodo_actual += 1;
  gpio_invertir_pin(PUERTO0,PIN26);

  if (g_semiperiodo_actual >= g_semiperiodos_nota_actual) {
    g_nota_actual += 1;
    siguiente_nota = g_ptr_melodia->ptr_notas[g_nota_actual];
    tipo_nota = g_ptr_melodia->ptr_duracion_nota[g_nota_actual];

    if (siguiente_nota != SONIDO_NOTA_FIN) {
      g_semiperiodo_actual = 0;
      if (siguiente_nota != SONIDO_NOTA_PAUSA) {
        uint16_t t_2_nota_us = 1E6 / (2 * siguiente_nota);
        uint32_t duracion_us_nota_actual = ((tipo_nota > 0 ? 1 : 1.5) * g_duracion_us_notas) /
                                           abs(tipo_nota);
        g_semiperiodos_nota_actual = duracion_us_nota_actual / t_2_nota_us;

        SONIDO_TIMER->MR0 = t_2_nota_us;
        SONIDO_TIMER->TC = 0;
      } else {
        g_semiperiodos_nota_actual = 1;

        gpio_pin_a_0(PUERTO0, PIN26);

        SONIDO_TIMER->MR0 = g_duracion_us_notas;
        SONIDO_TIMER->TC = 0;
      }
    } else {
      SONIDO_TIMER->TCR = 0;
      g_reproduciendo = FALSE;
    }
  }
  SONIDO_TIMER->IR = 1;
}
