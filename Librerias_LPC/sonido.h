/**
 * @file    sonido.h
 * @brief   Funciones básicas de sonido.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef SONIDO_H
#define SONIDO_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

/**
 * @name    Simbolos del TIMER utilizado por la librería de sonido.
 * @ingroup Sonido
 * @{
 */
#define SONIDO_TIMER                  TIMER3             //!< Timer utilizado.
#define SONIDO_TIMER_IRQn             TIMER3_IRQn        //!< Número de la int. del timer utilizado.
#define SONIDO_TIMER_IRQHandler       TIMER3_IRQHandler  //!< Manejador de int. del timer utilizado.
#define SONIDO_PRIORIDAD_INTERRUPCION 31u                //!< Prioridad de la interrupción.
//!@}

/**
 * @brief   Frecuencia [Hz] de las notas según la notación anglosajona
 * @ingroup Sonido
 */
enum sonido_timer_config {
  SONIDO_NOTA_FIN   = 1,
  SONIDO_NOTA_B0    = 31, // Si
  SONIDO_NOTA_C1    = 33,
  SONIDO_NOTA_CS1   = 35,
  SONIDO_NOTA_D1    = 37,
  SONIDO_NOTA_DS1   = 39,
  SONIDO_NOTA_E1    = 41,
  SONIDO_NOTA_F1    = 44,
  SONIDO_NOTA_FS1   = 46,
  SONIDO_NOTA_G1    = 49,
  SONIDO_NOTA_GS1   = 52,
  SONIDO_NOTA_A1    = 55,  // La
  SONIDO_NOTA_AS1   = 58,
  SONIDO_NOTA_B1    = 62,
  SONIDO_NOTA_C2    = 65,
  SONIDO_NOTA_CS2   = 69,
  SONIDO_NOTA_D2    = 73,
  SONIDO_NOTA_DS2   = 78,
  SONIDO_NOTA_E2    = 82,
  SONIDO_NOTA_F2    = 87,
  SONIDO_NOTA_FS2   = 93,
  SONIDO_NOTA_G2    = 98,
  SONIDO_NOTA_GS2   = 104,
  SONIDO_NOTA_A2    = 110,
  SONIDO_NOTA_AS2   = 117,
  SONIDO_NOTA_B2    = 123,
  SONIDO_NOTA_C3    = 131,
  SONIDO_NOTA_CS3   = 139,
  SONIDO_NOTA_D3    = 147,
  SONIDO_NOTA_DS3   = 156,
  SONIDO_NOTA_E3    = 165,
  SONIDO_NOTA_F3    = 175,
  SONIDO_NOTA_FS3   = 185,
  SONIDO_NOTA_G3    = 196,
  SONIDO_NOTA_GS3   = 208,
  SONIDO_NOTA_A3    = 220,
  SONIDO_NOTA_AS3   = 233,
  SONIDO_NOTA_B3    = 247,
  SONIDO_NOTA_C4    = 262,
  SONIDO_NOTA_CS4   = 277,
  SONIDO_NOTA_D4    = 294,
  SONIDO_NOTA_DS4   = 311,
  SONIDO_NOTA_E4    = 330,
  SONIDO_NOTA_F4    = 349,
  SONIDO_NOTA_FS4   = 370,
  SONIDO_NOTA_G4    = 392,
  SONIDO_NOTA_GS4   = 415,
  SONIDO_NOTA_A4    = 440,
  SONIDO_NOTA_AS4   = 466,
  SONIDO_NOTA_B4    = 494,
  SONIDO_NOTA_C5    = 523,
  SONIDO_NOTA_CS5   = 554,
  SONIDO_NOTA_D5    = 587,
  SONIDO_NOTA_DS5   = 622,
  SONIDO_NOTA_E5    = 659,
  SONIDO_NOTA_F5    = 698,
  SONIDO_NOTA_FS5   = 740,
  SONIDO_NOTA_G5    = 784,
  SONIDO_NOTA_GS5   = 831,
  SONIDO_NOTA_A5    = 880,
  SONIDO_NOTA_AS5   = 932,
  SONIDO_NOTA_B5    = 988,
  SONIDO_NOTA_C6    = 1047,
  SONIDO_NOTA_CS6   = 1109,
  SONIDO_NOTA_D6    = 1175,
  SONIDO_NOTA_DS6   = 1245,
  SONIDO_NOTA_E6    = 1319,
  SONIDO_NOTA_F6    = 1397,
  SONIDO_NOTA_FS6   = 1480,
  SONIDO_NOTA_G6    = 1568,
  SONIDO_NOTA_GS6   = 1661,
  SONIDO_NOTA_A6    = 1760,
  SONIDO_NOTA_AS6   = 1865,
  SONIDO_NOTA_B6    = 1976,
  SONIDO_NOTA_C7    = 2093,
  SONIDO_NOTA_CS7   = 2217,
  SONIDO_NOTA_D7    = 2349,
  SONIDO_NOTA_DS7   = 2489,
  SONIDO_NOTA_E7    = 2637,
  SONIDO_NOTA_F7    = 2794,
  SONIDO_NOTA_FS7   = 2960,
  SONIDO_NOTA_G7    = 3136,
  SONIDO_NOTA_GS7   = 3322,
  SONIDO_NOTA_A7    = 3520,
  SONIDO_NOTA_AS7   = 3729,
  SONIDO_NOTA_B7    = 3951,
  SONIDO_NOTA_C8    = 4186,
  SONIDO_NOTA_CS8   = 4435,
  SONIDO_NOTA_D8    = 4699,
  SONIDO_NOTA_DS8   = 4978,
  SONIDO_NOTA_PAUSA = 0      // Silencio
};

/**
 * @brief   Array de conversión de nota a semiperiodo en microsegundos.
 * @ingroup Sonido
 *
 * @note El índice 0 no se usa porque la nota 0 indicará silencio.
 */
static const uint16_t kNotaASemiperiodoUs[] = {
        0,
    16198,  // B0
    15289,  // C1
    14431,  // CS1
    13621,  // D1
    12856,  // DS1
    12135,  // E1
    11454,  // F1
    10811,  // FS1
    10204,  // G1
     9631,  // GS1
     9091,  // A1
     8581,  // AS1
     8099,  // B1
     7645,  // C2
     7215,  // CS2
     6810,  // D2
     6428,  // DS2
     6067,  // E2
     5727,  // F2
     5405,  // FS2
     5102,  // G2
     4816,  // GS2
     4545,  // A2
     4290,  // AS2
     4050,  // B2
     3822,  // C3
     3608,  // CS3
     3405,  // D3
     3214,  // DS3
     3034,  // E3
     2863,  // F3
     2703,  // FS3
     2551,  // G3
     2408,  // GS3
     2273,  // A3
     2145,  // AS3
     2025,  // B3
     1911,  // C4
     1804,  // CS4
     1703,  // D4
     1607,  // DS4
     1517,  // E4
     1432,  // F4
     1351,  // FS4
     1276,  // G4
     1204,  // GS4
     1136,  // A4
     1073,  // AS4
     1012,  // B4
      956,  // C5
      902,  // CS5
      851,  // D5
      804,  // DS5
      758,  // E5
      716,  // F5
      676,  // FS5
      638,  // G5
      602,  // GS5
      568,  // A5
      536,  // AS5
      506,  // B5
      478,  // C6
      451,  // CS6
      426,  // D6
      402,  // DS6
      379,  // E6
      358,  // F6
      338,  // FS6
      319,  // G6
      301,  // GS6
      284,  // A6
      268,  // AS6
      253,  // B6
      239,  // C7
      225,  // CS7
      213,  // D7
      201,  // DS7
      190,  // E7
      179,  // F7
      169,  // FS7
      159,  // G7
      150,  // GS7
      142,  // A7
      134,  // AS7
      127,  // B7
      119   // C8
};

/**
 * @brief   Estructura para definir las melodías.
 * @ingroup Sonido
 */
typedef struct{
  uint16_t tempo;                   //!< Tempo de la melodía.
  uint16_t numero_notas;            //!< Número de notas de la melodía.
  const uint16_t *ptr_notas;        //!< Puntero al array de notas.

  /**
   * @brief   Duración de las notas.
   *
   * @details  Los números negativos se utilizan para representar las notas con puntillo.
   *
   *  Número  |    Nota
   * :------: | :----------
   *   1      |   Redonda
   *   2      |   Blanca
   *   4      |   Negra
   *   8      |   Corchea
   *   16     |   Semicorchea
   *   -4     |   Negra con puntillo
   *   ...    |   ...
   */
  const int8_t *ptr_duracion_nota;
} sonido_melodia_t;

// ===== Sonido - Funciones Públicas =====
void sonido_emitir_pitido(uint32_t frecuencia, uint32_t duracion_ms);

void sonido_inicializar(void);
void sonido_reproducir_nota(uint8_t nota, uint32_t duracion_ms);
void sonido_iniciar_melodia(sonido_melodia_t *ptr_melodia);
void sonido_reproducir_melodia(const uint8_t *ptr_notas, uint32_t duracion_nota_ms);

#endif  // SONIDO_H
