/**
 * @file  lm75b_lpc40xx.c
 * @brief Funciones para acceder a un sensor de temperatura LM75B a través de una de las
 * interfaces I2C del LPC40xx.
 *
 * @details La tarjeta Embedded Artist Developer's Kit dispone de un LM75B integrado conectado a
 * la interfaz I2C0 en los siguiente pines:
 *
 * Pin uC | Función
 * ------ | ---------
 * P0[27] | SDA
 * P0[28] | SCL
 *
 * @author
 * @date
 * @version
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "lm75b_lpc40xx.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "error.h"
#include "i2c_lpc40xx.h"

/**
 * @defgroup  LM75B_Var_Privadas LM75B - Variables Privadas
 * @ingroup   LM75B
 * @details Variables globales estáticas para mantener los parámetros utilizados para la
 * comunicación con el LM75B. La función lm75b_inicializar almacena en ellas los valores que se
 * utilizarán en el resto de funciones.
 * @{
 */
/**
 * @brief   Interfaz I2C a la que está conectado el LM75B.
 * @ingroup LM75B
 * @private
 */
static LPC_I2C_TypeDef* lm75b_interfaz_i2c;

/**
 * @brief   Dirección I2c del LM75B a utilizar.
 * @ingroup LM75B
 * @private
 */
static uint8_t lm75b_dir_i2c;
//!@}

/**
 * @brief   Configura la interfaz I2C para la comunicación con el LM75B y devuelve si es el
 * dispositivo está disponible.
 * @ingroup LM75B
 *
 * @param[in] i2c_regs          Puntero a regs. de la interfaz a inicializar.
 * @param[in] frecuencia_scl    Frecuencia de la señal SCL.
 * @param[in] puerto_sda        Puerto que se desea para la función SDA.
 * @param[in] mascara_pin_sda   Pin que se desea para la función SDA.
 * @param[in] puerto_scl        Puerto que se desea para la función SCL.
 * @param[in] mascara_pin_scl   Pin que se desea para la función SCL.
 * @param[in] dir_i2c           Dirección I2C del LM75B.
 *
 * @retval    TRUE    Se ha podido establecer la comunicación con el LM75B.
 * @retval    FALSE   No se ha podido establecer la comunicación con el LM75B.
 */
bool_t lm75b_inicializar(LPC_I2C_TypeDef *i2c_regs, uint32_t frecuencia_scl,
                         LPC_GPIO_TypeDef *puerto_sda, uint32_t mascara_pin_sda,
                         LPC_GPIO_TypeDef *puerto_scl, uint32_t mascara_pin_scl, uint8_t dir_i2c) {

  /* Inicializar la interfaz I2C y almacenar los valores correspondientes de la interfaz I2C y la
   * dirección del dispositivo para utilizarlos en el resto de funciones.
   */

  //===== COMPLETAR =====

  /* Comprobar la comunicación con el LM75B transmitiendo su dirección y retornando el valor
   * devuelto por la función i2c_transmitir_byte. No olvidar enviar la señal de stop para liberar
   * el bus antes de regresar al programa principal.
   */

  //===== COMPLETAR =====
}

/**
 * @brief   Escribe un dato en un registro interno del LM75B.
 * @ingroup LM75B
 *
 * @param[in] dir_registro  Dirección del registro a escribir.
 * @param[in] dato          Dato a escribir en el registro.
 *
 * @note  Hay registros de 8 y 16 bits por lo que requieren de algortimos diferentes.
 */
void lm75b_escribir_registro(uint8_t dir_registro, uint16_t dato) {

  //===== COMPLETAR =====
}

/**
 * @brief   Lee un registro interno del LM75B.
 * @ingroup LM75B
 *
 * @param[in]   dir_registro   Dirección del registro a leer.
 *
 * @return  Valor leído del registro.
 *
 * @note  Hay registros de 8 y 16 bits por lo que requieren de algortimos diferentes.
 */
uint16_t lm75b_leer_registro(uint8_t dir_registro) {

  //===== COMPLETAR =====
}

/**
 * @brief   Lee el registro TEMP del LM75B y retorna la temperatura en grados centígrados.
 * @ingroup LM75B
 *
 * @return  Temperatura en grados centígrados.
 *
 * @note  Utiliza las funciones anteriormente creadas.
 */
float32_t lm75b_leer_temperatura(void) {

  //===== COMPLETAR =====
}
