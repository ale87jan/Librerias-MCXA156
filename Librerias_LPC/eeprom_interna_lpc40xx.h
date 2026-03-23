/**
 * @file    eeprom_interna_lpc40xx.h
 * @brief   Funciones para acceder a la EEPROM interna del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2025
 * @version 1.0
 *
 * @copyright   GNU General Public License version 3 or later
 *
 */

#ifndef EEPROM_LPC40XX_H
#define EEPROM_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "timer_lpc40xx.h"

// ===== EEPROM Interna - Constantes Publicas =====
/**
 * @brief   Símbolos para indicar las posibles instrucciones del registro CMD de la EEPROM.
 * @ingroup EEPROM Interna
 */
enum eeprom_interna_instrucciones {
  EEPROM_LEER_8      = 0,   //!< Leer 8 bits.
  EEPROM_LEER_16     = 1,   //!< Leer 16 bits.
  EEPROM_LEER_32     = 2,   //!< Leer 32 bits.
  EEPROM_ESCRIBIR_8  = 3,   //!< Escribir 8 bits.
  EEPROM_ESCRIBIR_16 = 4,   //!< Escribir 16 bits.
  EEPROM_ESCRIBIR_32 = 5,   //!< Escribir 32 bits.
  EEPROM_PROGRAMAR   = 6    //!< Escribir/borrar la página en caché a la EEPROM.
};

/**
 * @brief   Máscaras para comprobar el registro de estado.
 * @ingroup EEPROM Interna
 */
enum eeprom_interna_bits_estado {
  EEPROM_END_OF_RW   = (1u << 26),   //!< Operación de lectura/escritura finalizada.
  EEPROM_END_OF_PROG = (1u << 28)    //!< Operación de programación finalizada.
};

/**
 * @brief   Símbolos para establecer el número de bits de los datos.
 * @ingroup EEPROM Interna
 */
typedef enum {
  EEPROM_8BITS  = 8,    //!< Dato de 8 bits.
  EEPROM_16BITS = 16,   //!< Dato de 16 bits.
  EEPROM_32BITS = 32,   //!< Dato de 32 bits.
} eeprom_interna_bits_dato;

// ===== EEPROM Interna - Funciones Publicas =====
void eeprom_interna_inicializar(void);

bool_t eeprom_interna_escritura_en_curso(void);
bool_t eeprom_interna_programacion_en_curso(void);

void eeprom_interna_limpiar_escritura_en_curso(void);
void eeprom_interna_limpiar_programacion_en_curso(void);

uint32_t eeprom_interna_leer_dato(uint16_t direccion, eeprom_interna_bits_dato tam);
void eeprom_interna_leer_datos(uint16_t direccion, eeprom_interna_bits_dato tam, uint32_t ptr_datos,
                               uint8_t n);

void eeprom_interna_escribir_dato(uint16_t direccion, eeprom_interna_bits_dato tam, uint32_t dato);
void eeprom_interna_escribir_datos(uint16_t direccion, eeprom_interna_bits_dato tam, uint32_t ptr_datos,
                                   uint8_t n);

#endif  // EEPROM_LPC40XX_H
