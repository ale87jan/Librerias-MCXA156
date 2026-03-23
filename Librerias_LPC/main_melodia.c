/**
 * @file  main_melodia.c
 * @brief Programa principal de ejemplo de reproducción de una melodía.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2025
 * @version 1.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "sonido.h"
#include "sonido_mario.h"

extern volatile uint16_t nota_actual;
extern volatile uint16_t duracion_us_notas;
extern volatile uint32_t semiperiodos_nota_actual;

int main(void) {

  glcd_inicializar();
  sonido_inicializar();
  glcd_borrar(NEGRO);

  sonido_iniciar_melodia(mario_theme);

  glcd_xprintf(0, 32 * 0, BLANCO, NEGRO, FUENTE16X32, "Duracion notas: %d", duracion_us_notas);
  glcd_xprintf(0, 32 * 1, BLANCO, NEGRO, FUENTE16X32, "Tempo: %d", mario_theme.tempo);
  glcd_xprintf(0, 32 * 2, BLANCO, NEGRO, FUENTE16X32, "Num notas: %d", mario_theme.numero_notas);

  while (1) {
    glcd_xprintf(0, 32 * 3, BLANCO, NEGRO, FUENTE16X32, "Nota: %d", nota_actual);
    glcd_xprintf(0, 32 * 4, BLANCO, NEGRO, FUENTE16X32, "T us: %d", semiperiodos_nota_actual);
  }
}
