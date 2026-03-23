/**
 * @file  eeprom_lpc40xx.c
 * @brief Funciones para acceder a una EEPROM 25LC160 a través de una interfaz SSP del LPC40xx.
 *
 * @details Se recomienda utilizar la interfaz SSP2 que está disponible en el conector J15 y nos
 * permite tener agrupadas las señales de manera más cómoda que en los conectores J3/J5.
 *
 * Pin uC | Función
 * ------ | --------------
 * P5[0]  | SSP2-MOSI
 * P5[1]  | SSP2-MISO
 * P5[2]  | SSP2-SCK
 * P2[14] | CS (tipo GPIO)
 *
 * @author    Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date      2014/2025
 * @version   2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "eeprom_lpc40xx.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "error.h"
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "spi_lpc40xx.h"

/**
 * @defgroup  EEPROM_Var_Privadas EEPROM - Variables Privadas
 * @ingroup   EEPROM
 *
 * @details   Variables globales estáticas (privadas a este módulo) para mantener los parámetros
 * utilizados para el acceso a la EEPROM. La función eeprom_inicializar almacena los valores que
 * se utilizarán en el resto de funciones.
 * @{
 */
static LPC_SSP_TypeDef   *eeprom_ssp;             //!< Interfaz SSP a usar.
static LPC_GPIO_TypeDef  *eeprom_puerto_cs;       //!< Puerto para señal /CS.
static uint32_t           eeprom_mascara_pin_cs;  //!< Pin para señal /CS.
static bool_t             eeprom_funcion_cs;      //!< Indica si se utiliza un pin como GPIO para la señal CS.
static LPC_TIM_TypeDef   *eeprom_timer;           //!< Timer a usar para retardos.
//!@}

/**
 * @brief   Inicializa la comunicación SPI entre el uC y la memoria 25LC160.
 * @ingroup EEPROM
 *
 * @param[in]   interfaz_ssp     Puntero a regs. de interfaz SSP a usar.
 * @param[in]   frecuencia_sck   Frecuencia de reloj a usar (en hercios).
 * @param[in]   puerto_sck       Puntero a regs. GPIO de puerto para señal SCK.
 * @param[in]   mascara_pin_sck  Máscara de seleccion de pin para señal SCK.
 * @param[in]   puerto_miso      Puntero a regs. GPIO de puerto para señal MISO.
 * @param[in]   mascara_pin_miso Máscara de seleccion de pin para señal MISO.
 * @param[in]   puerto_mosi      Puntero a regs. GPIO de puerto para señal MOSI.
 * @param[in]   mascara_pin_mosi Máscara de seleccion de pin para señal MOSI.
 * @param[in]   puerto_cs         Puntero a regs. GPIO para la señal CS.
 * @param[in]   mascara_pin_cs    Máscara de seleccion de pin para la señal CS.
 * @param[in]   funcion_cs        Verdadero si se utiliza un pin con función CS.
 * @param[in]   timer            Puntero a regs. de timer para retardos.
 *
 * @warning   El timer indicado se reconfigurará como retardo bloqueante en microsegundos cuando
 * se utilice con un pin sin función CS/SSEL. No es necesario que se inicialice con anterioridad.
 */
void eeprom_inicializar(LPC_SSP_TypeDef *interfaz_ssp, uint32_t frecuencia_sck,
                        LPC_GPIO_TypeDef *puerto_sck, uint32_t mascara_pin_sck,
                        LPC_GPIO_TypeDef *puerto_miso, uint32_t mascara_pin_miso,
                        LPC_GPIO_TypeDef *puerto_mosi, uint32_t mascara_pin_mosi,
                        LPC_GPIO_TypeDef *puerto_cs, uint32_t mascara_pin_cs,
                        bool_t funcion_cs, LPC_TIM_TypeDef *timer) {

  // Inicializar la interfaz SSP con Datos de 8 bits, CPOL = 0, CPHA = 0
  spi_inicializar(interfaz_ssp, SPI_DATOS_8_BITS, frecuencia_sck, SPI_CPOL_0, SPI_CPHA_0,
                  puerto_sck, mascara_pin_sck, puerto_miso, mascara_pin_miso,
                  puerto_mosi, mascara_pin_mosi, puerto_cs, mascara_pin_cs, funcion_cs);

  /* Ajustar el valor de las variables que indicarán al resto de funciones de comunicación con la 
   * EEPROM la interfaz SSP, el pin para la señal CS y el timer a emplear cuando haya que realizar 
   * retardos.
   */
  eeprom_ssp = interfaz_ssp;
  eeprom_puerto_cs = puerto_cs;
  eeprom_mascara_pin_cs = mascara_pin_cs;
  eeprom_funcion_cs = funcion_cs;
  eeprom_timer = timer;

  if (!funcion_cs) {
    timer_inicializar(timer);
  }
}

/**
 * @brief   Pone la línea chip select de la EEPROM 25LC160 a 0 o a 1.
 * @ingroup EEPROM
 *
 * @param[in]   nivel   Nivel al que debe ponerse la línea chip select.
 */
void eeprom_chip_select(bool_t nivel) {

  // Realizar un retardo de 5 us
  timer_retardo_us(eeprom_timer, 5);

  /* Ajustar el nivel en el pin indicado por las variables eeprom_puerto_cs y eeprom_mascara_pin_cs
   * según indica el argumento de la función. Puede usarse la función gpio_escribir_pin del
   * fichero gpio_lpc40xx.h.
   */
  gpio_escribir_pin(eeprom_puerto_cs, eeprom_mascara_pin_cs, nivel);

  // Realizar un retardo de 5 us
  timer_retardo_us(eeprom_timer, 5);
}

/**
 * @brief   Comprobar si en este momento hay una escritura en curso en la EEPROM 25LC160.
 * @ingroup EEPROM
 *
 * @retval  TRUE => hay una escritura en curso.
 * @retval  FALSE => no hay una escritura en curso.
 */
bool_t eeprom_escritura_en_curso(void) {

  // Retornar TRUE o FALSE según el bit WIP (bit 0) del registro de estado esté a 1 o a 0.
  return (eeprom_leer_reg_estado() & EEPROM_STATUS_WIP) != 0;
}

/**
 * @brief   Lee un byte de la EEPROM 25LC160.
 * @ingroup EEPROM
 *
 * @param[in]   direccion   Dirección de la EEPROM que se quiere leer. Debe estar entre 0 y 2047.
 *
 * @return      Byte leído.
 */
uint8_t eeprom_leer_byte(uint16_t direccion) {

  uint8_t d;

  /* Comprobar que la dirección está en el rango de 0 a 2047. Si no es así, abortar el programa
   * (usa la macro ASSERT de error.h).
   */
  ASSERT(direccion < 2*1024, "La dirección debe estar entre 0 y 0x7FF");

  // Esperar mientras haya una escritura en curso en la EEPROM
  while (eeprom_escritura_en_curso()) {;}

  // Leer el byte siguiendo la secuencia "Read sequence" del cronograma de la 25LC160
  if (!eeprom_funcion_cs) {
    eeprom_chip_select(0);
  }

  spi_transferir(eeprom_ssp, EEPROM_READ);

  spi_transferir(eeprom_ssp, (direccion >> 8) & 0xFF);
  spi_transferir(eeprom_ssp, direccion & 0xFF);

  // Transferimos un byte vacio (0) para que la EEPROM nos retorne el valor solicitado
  d = spi_transferir(eeprom_ssp, 0);

  if (!eeprom_funcion_cs) {
    eeprom_chip_select(1);
  }

  // Retornar el byte leído
  return d;
}

/**
 * @brief   Escribe un byte en la EEPROM 25LC160.
 * @ingroup EEPROM
 *
 * @param[in]   direccion   Dirección de la EEPROM donde se quiere escribir. Debe estar entre
                            0 y 2047.
 * @param[in]   byte        Byte que se quiere escribir.
 */
void eeprom_escribir_byte(uint16_t direccion, uint8_t byte) {

  /* Comprobar que la dirección está en el rango de 0 a 2047. Si no es así, abortar el programa
   * (usa la macro ASSERT de error.h).
   */
  ASSERT(direccion < 2*1024, "La dirección debe estar entre 0 y 0x7FF");

  // Esperar mientras haya una escritura en curso en la EEPROM.
  while (eeprom_escritura_en_curso()) {;}

  /* Enviar el comando de habilitación de escritura realizando los pasos
   * del cronograma "Write enable sequence" del datasheet.
   */
  if (!eeprom_funcion_cs) {
    eeprom_chip_select(0);
  }

  spi_transferir(eeprom_ssp, EEPROM_WREN);

  if (!eeprom_funcion_cs) {
    eeprom_chip_select(1);
  }

  // Llevar a cabo los pasos de la secuencia "Byte write sequence" según el datasheet
  if (!eeprom_funcion_cs) {
    eeprom_chip_select(0);
  }

  spi_transferir(eeprom_ssp, EEPROM_WRITE);

  spi_transferir(eeprom_ssp, (direccion >> 8) & 0xFF);
  spi_transferir(eeprom_ssp, direccion & 0xFF);

  spi_transferir(eeprom_ssp, byte);

  if (!eeprom_funcion_cs) {
    eeprom_chip_select(1);
  }
}
/**
 * @brief   Lee el registro de estado de la EEPROM 25LC160.
 * @ingroup EEPROM
 *
 * @return  Valor del registro de estado de la EEPROM.
 */
uint8_t eeprom_leer_reg_estado(void) {
  uint8_t status;

  /* Leer el registro de estado de la 25LC160 según el cronograma "Read status register timing
   * sequence" del datasheet.
   */
  if (!eeprom_funcion_cs) {
    eeprom_chip_select(0);
  }

  spi_transferir(eeprom_ssp, EEPROM_RDSR);

  // Transferimos un byte vacio (0) para que la EEPROM nos retorne el valor solicitado
  status = spi_transferir(eeprom_ssp, 0);

  if (!eeprom_funcion_cs) {
    eeprom_chip_select(1);
  }

  return status;
}
/**
 * @brief   Escribe el registro de estado de la EEPROM 25LC160. BP0 y BP1 a 0.
 * @ingroup EEPROM
 */
void eeprom_escribir_reg_estado(uint8_t byte) {

  /* Escribir el registro de estado de la 25LC160 según el cronograma "Write status register timing
   * sequence" del datasheet.
   */
  if (!eeprom_funcion_cs) {
    eeprom_chip_select(0);
  }

  spi_transferir(eeprom_ssp, EEPROM_WRSR);

  spi_transferir(eeprom_ssp, byte);

  if (!eeprom_funcion_cs) {
    eeprom_chip_select(1);
  }
}
