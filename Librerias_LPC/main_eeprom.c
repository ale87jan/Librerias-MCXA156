/**
 * @file  main_eeprom.c
 * @brief Programa principal del acceso a una memoria EEPROM 25LC160 a través de la interfaz SSP2
 * del LPC40xx.
 *
 * @author      Alejandro Lara Doña - alejandro.lara@uca.es
 * @date        2025
 * @version     1.0
 *
 * @copyright   GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "gpio_lpc40xx.h"
#include "eeprom_lpc40xx.h"

int main(void) {
  volatile uint8_t dato_leido;
  uint8_t i, estado_antes, estado_despues;
  uint16_t pos_x = 0, pos_y = 0;

  glcd_inicializar();
  timer_inicializar(TIMER0);
  eeprom_inicializar(SSP2,            // Interfaz SSP para acceder a la EEPROM
                     500000,          // Frecuencia SCK
                     PUERTO5, PIN2,   // Puerto/pin para SCK
                     PUERTO5, PIN1,   // Puerto/pin para MISO
                     PUERTO5, PIN0,   // Puerto/pin para MOSI
                     PUERTO2, PIN14,  // Puerto/pin para CS
                     FALSE,           // CS en un pin estándar sin función CS
                     TIMER0);         // Timer usado durante el acceso a la EEPROM

  eeprom_escribir_reg_estado(0);
  estado_antes = eeprom_leer_reg_estado();

  for (i = 0; i <= 40; i++) {
    eeprom_escribir_byte(i, 0xA5);
  }

  for (i = 0;i <= 43; i++) {
    dato_leido = eeprom_leer_byte(i);
    glcd_xprintf(pos_x, pos_y, BLANCO, NEGRO, FUENTE12X24, "%04d %02X ", i, dato_leido);

    pos_x += 96;

    if (pos_x >= 480) {
      pos_x = 0;
      pos_y += 24;
    }
  }

  estado_despues = eeprom_leer_reg_estado();

  glcd_xprintf(0, pos_y + 24, BLANCO, NEGRO, FUENTE12X24,
               "reg estado antes= %02x", estado_antes);
  
  glcd_xprintf(0, pos_y + 48, BLANCO, NEGRO, FUENTE12X24,
               "reg estado despues= %02x", estado_despues);
  while (1) {
    ;
  }
}
