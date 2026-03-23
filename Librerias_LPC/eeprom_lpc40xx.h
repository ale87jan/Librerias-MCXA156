/**
 * @file  eeprom_lpc40xx.h
 * @brief Funciones para acceder a una EEPROM 24LC160 a través de una interfaz SSP del LPC40xx.
 *
 * @author    Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date      2014/2025
 * @version   2.0
 *
 * @copyright GNU General Public License version 3 or later
 *
 */

#ifndef EEPROM_LPC40XX_H
#define EEPROM_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "timer_lpc40xx.h"
#include "spi_lpc40xx.h"

// ===== EEPROM - Constantes Publicas =====
/**
 * @brief   Símbolos para indicar las instrucciones de la EEPROM 25LC160.
 * @ingroup EEPROM
 */
enum eeprom_instrucciones {
  EEPROM_READ  = 3,   //!< Leer datos de memoria empezando en la dirección indicada.
  EEPROM_WRITE = 2,   //!< Escribir datos en memoria empezando en la dirección indicada.
  EEPROM_WRDI  = 4,   //!< Deshabilitar operaciones de escritura (reset write enable latch).
  EEPROM_WREN  = 6,   //!< Habilitar operaciones de escritura (set write enable latch).
  EEPROM_RDSR  = 5,   //!< Leer registro de estado (STATUS).
  EEPROM_WRSR  = 1    //!< Escribir registro de estado (STATUS).
};

/**
 * @brief   Máscaras para comprobar el registro de estado.
 * @ingroup EEPROM
 */
enum eeprom_bits_estado {
  EEPROM_STATUS_WIP  = (1u << 0),   //!< Write In Process.
  EEPROM_STATUS_WEL  = (1u << 1),   //!< Write Enable Latcht.
  EEPROM_STATUS_BP0  = (1u << 2),   //!< Block Protection 0.
  EEPROM_STATUS_BP1  = (1u << 3),   //!< Block Protection 1.
  EEPROM_STATUS_WPEN = (1u << 7)    //!< Write Protect Enable.
};

// ===== EEPROM - Funciones Publicas =====
void eeprom_inicializar(LPC_SSP_TypeDef *interfaz_ssp, uint32_t frecuencia_sck,
                        LPC_GPIO_TypeDef *puerto_sck, uint32_t mascara_pin_sck,
                        LPC_GPIO_TypeDef *puerto_miso, uint32_t mascara_pin_miso,
                        LPC_GPIO_TypeDef *puerto_mosi, uint32_t mascara_pin_mosi,
                        LPC_GPIO_TypeDef *puerto_cs, uint32_t mascara_pin_cs,
                        bool_t funcion_cs, LPC_TIM_TypeDef *timer);

void eeprom_chip_select(bool_t nivel);
bool_t eeprom_escritura_en_curso(void);

uint8_t eeprom_leer_byte(uint16_t direccion);
void eeprom_escribir_byte(uint16_t direccion, uint8_t dato);

uint8_t eeprom_leer_reg_estado(void);
void eeprom_escribir_reg_estado(uint8_t byte);

#endif  // EEPROM_LPC40XX_H
