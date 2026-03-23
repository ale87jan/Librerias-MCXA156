/**
 * @file  lm75b_lpc40xx.h
 * @brief Funciones para acceder a un sensor de temperatura LM75B a través de una de las
 * interfaces I2C del LPC40xx.
 *
 * @author    Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date      2014/2025
 * @version   2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef LM75B_LPC40XX_H
#define LM75B_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

// ===== LM75B - Constantes Publicas =====
/**
 * @brief   Dirección I2C del LM75B en la tarjeta EA LPC4088 Developer's Kit.
 * @ingroup LM75B
 */
#define LM75B_DIR_I2C   0x48

/**
 * @brief   Constantes para las direcciones de los registros del LM75B.
 * @ingroup LM75B
 */
enum lm75b_registros {
  LM75B_REG_TEMP  = 0,
  LM75B_REG_CONF  = 1,
  LM75B_REG_THYST = 2,
  LM75B_REG_TOS   = 3
};

// ===== LM75B - Funciones Públicas =====
bool_t lm75b_inicializar(LPC_I2C_TypeDef *i2c_regs, uint32_t frecuencia_scl,
                         LPC_GPIO_TypeDef *puerto_sda, uint32_t mascara_pin_sda,
                         LPC_GPIO_TypeDef *puerto_scl, uint32_t mascara_pin_scl, uint8_t dir_i2c);
void lm75b_escribir_registro(uint8_t dir_registro, uint16_t dato);
uint16_t lm75b_leer_registro(uint8_t dir_registro);
float32_t lm75b_leer_temperatura(void);

#endif  // LM75B_LPC40XX_H
