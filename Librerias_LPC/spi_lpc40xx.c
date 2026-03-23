/**
 * @file  spi_lpc40xx.c
 * @brief Funciones básicas para usar las interfaces SSP del LPC40xx en modo maestro SPI.
 *
 * @author    Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date      2014/2025
 * @version   2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "spi_lpc40xx.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "error.h"
#include "iocon_lpc40xx.h"
#include "gpio_lpc40xx.h"

/**
 * @brief   Inicializar una interfaz SSP del LP40xx en modo maestro SPI.
 * @ingroup SPI
 *
 * @param[in]   ssp_regs          Puntero a regs. de interfaz SSP a inicializar.
 * @param[in]   numero_bits_datos Núm. de bits que tendrán los datos que se transferirán.
 * @param[in]   frecuencia_sck    Frecuencia de reloj a usar.
 * @param[in]   cpol              Polaridad de reloj (0 o 1).
 * @param[in]   cpha              Fase de reloj (0 o 1).
 * @param[in]   puerto_sck        Puntero a regs. GPIO para la señal SCK.
 * @param[in]   mascara_pin_sck   Máscara de seleccion de pin para la señal SCK.
 * @param[in]   puerto_miso       Puntero a regs. GPIO para la señal MISO.
 * @param[in]   mascara_pin_miso  Máscara de seleccion de pin para la señal MISO.
 * @param[in]   puerto_mosi       Puntero a regs. GPIO para la señal MOSI.
 * @param[in]   mascara_pin_mosi  Máscara de seleccion de pin para la señal MOSI.
 * @param[in]   puerto_cs         Puntero a regs. GPIO para la señal CS.
 * @param[in]   mascara_pin_cs    Máscara de seleccion de pin para la señal CS.
 * @param[in]   funcion_cs        Verdadero si se utiliza un pin con función CS.
 */
void spi_inicializar(LPC_SSP_TypeDef *ssp_regs, uint32_t numero_bits_datos,
                     uint32_t frecuencia_sck, uint32_t cpol, uint32_t cpha,
                     LPC_GPIO_TypeDef *puerto_sck, uint32_t mascara_pin_sck,
                     LPC_GPIO_TypeDef *puerto_miso, uint32_t mascara_pin_miso,
                     LPC_GPIO_TypeDef *puerto_mosi, uint32_t mascara_pin_mosi,
                     LPC_GPIO_TypeDef *puerto_cs,   uint32_t mascara_pin_cs,
                     bool_t funcion_cs) {

  uint32_t valor_scr;
  uint8_t i;

  // Comprobar los parámetros
  ASSERT(numero_bits_datos >= SPI_DATOS_4_BITS && numero_bits_datos <= SPI_DATOS_16_BITS,
         "El número de bits de los datos debe estar entre 4 y 16.");

  ASSERT(cpol == 0 || cpol == 1, "CPOL debe ser 0 o 1");

  ASSERT(cpha == 0 || cpha == 1, "CPHA debe ser 0 o 1");

  ASSERT(PeripheralClock / 2 >= frecuencia_sck,
         "La frecuencia de reloj (SCK) seleccionada es demasiado elevada.");

  valor_scr = PeripheralClock / (2 * frecuencia_sck);
  ASSERT(valor_scr <= 256, "La frecuencia de reloj (SCK) seleccionada es demasiado baja.");

  // Asegurar que la interfaz seleccionado no está en modo de bajo consumo
  if (ssp_regs == SSP0) {
    LPC_SC->PCONP |= (1u << 21);

  } else if (ssp_regs == SSP1) {
    LPC_SC->PCONP |= (1u << 10);

  } else if (ssp_regs == SSP2) {
    LPC_SC->PCONP |= (1u << 20);
  }

  // Asegurarse de que la interfaz está deshabilitado mientras se configura
  ssp_regs->CR1 = 0;

  /* El registro CPSR se programará con el valor fijo 2 para simplificar el ajuste de la
   * frecuencia de SCK.
   */
  ssp_regs->CPSR = 2;

  /* En el registro CR0, programar el número de bits de datos, modo SPI, CPOL, CPHA y
   * valor del divisor SCR.
   */
  ssp_regs->CR0 = (numero_bits_datos - 1) | (cpol << 6) | (cpha << 7) | (valor_scr << 8);

  // Leer el registro de datos (DR) 8 veces para vaciar la FIFO de recepción
  for (i = 0; i < 8; i++) {
    uint16_t temp = ssp_regs->DR;
  }

  // Seleccionar las funciones SSPn_SCK, SSPn_MISO y SSPn_MOSI en los pines indicados
  if (ssp_regs == SSP0) {
    iocon_configurar_pin(puerto_sck, mascara_pin_sck, SSP0_SCK, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_miso, mascara_pin_miso, SSP0_MISO, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_mosi, mascara_pin_mosi, SSP0_MOSI, IOCON_NO_PULL_UP_NO_PULL_DOWN);

    // Si el pin utilizado para la señal de chip select tiene función CS/SSEL, seleccionarla
    if (funcion_cs) {
      iocon_configurar_pin(puerto_cs, mascara_pin_cs, SSP0_SSEL, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    }

  } else if (ssp_regs == SSP1) {
    iocon_configurar_pin(puerto_sck, mascara_pin_sck, SSP1_SCK, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_miso, mascara_pin_miso, SSP1_MISO, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_mosi, mascara_pin_mosi, SSP1_MOSI, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    if (funcion_cs) {
      iocon_configurar_pin(puerto_cs, mascara_pin_cs, SSP1_SSEL, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    }

  } else if (ssp_regs == SSP2) {
    iocon_configurar_pin(puerto_sck, mascara_pin_sck, SSP2_SCK, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_miso, mascara_pin_miso, SSP2_MISO, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    iocon_configurar_pin(puerto_mosi, mascara_pin_mosi, SSP2_MOSI, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    if (funcion_cs) {
      iocon_configurar_pin(puerto_cs, mascara_pin_cs, SSP2_SSEL, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    }
  }

  /* Si el pin utilizado para la señal de chip select no tiene función CS/SSEL, configurarlo como
   * gpio, dirección salida y valor inicial de 1.
   */
  if (!funcion_cs) {
    iocon_configurar_pin(puerto_cs, mascara_pin_cs, GPIO, IOCON_NO_PULL_UP_NO_PULL_DOWN);
    gpio_ajustar_dir(puerto_cs, mascara_pin_cs, DIR_SALIDA);
    gpio_pin_a_1(puerto_cs, mascara_pin_cs);
  }

  // En el registro CR1, seleccionar el modo maestro y habilitar la interfaz
  ssp_regs->CR1 = 1u << 1;
}

/**
 * @brief   Realizar una transferencia a través de una interfaz SSP del LPC40xx en modo SPI. La
 * función no retorna hasta que termine la transferencia.
 * @ingroup SPI
 *
 * @param[in]   ssp_regs            Puntero a regs. de interfaz SSP.
 * @param[in]   dato_a_transmitir   Dato a enviar al esclavo. Sólo se enviarán los bits de 0 a
 *                                  n-1, siendo n el número de bits de datos para el que ha sido
 *                                  configurada la interfaz.
 *
 * @return      Dato recibido desde el esclavo. Sólo son significativos los bits de 0 a n-1, siendo
 * n el número de bits de datos para el que ha sido configurada la interfaz.
 */
uint16_t spi_transferir(LPC_SSP_TypeDef *ssp_regs, uint16_t dato_a_transmitir) {

  /* Esperar hasta que el bit TNF (Transmit FIFO Not Full) del registro de estado de la interfaz
   * esté a 1, indicando así que hay espacio en la FIFO de transmisión.
   */
  while ((ssp_regs->SR & (1u << 1)) == 0) {;}

  /* Escribir el dato a transmitir en el registro de datos. Esto hace que ingrese en la FIFO de
   * transmisión. Si en este momento la FIFO de transmisión está vacía, la transmisión del dato
   * comienza inmediatamente.
   */
  ssp_regs->DR = dato_a_transmitir;

  /* Esperar hasta que el bit RNE (Receive FIFO Not Empty) del registro de estado de la interfaz
   * esté a 1, indicando así que hay al menos un dato en la FIFO de recepción.
   */
  while ((ssp_regs->SR & (1u << 2)) == 0) {;}

  // Leer un dato de la FIFO de recepción y retornarlo
  return ssp_regs->DR;
}
