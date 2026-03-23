/**
 * @file    error.c
 * @brief   Librería para el tratamiento de errores.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "error.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

/**
 * @brief Inclusión condicional si se está utilizando la pantalla GLCD de EA para el LPC4088.
 */
#ifdef EA_GLCD
  #include "glcd.h"
#endif

/**
 * @brief   Función que es llamada por la macro ERROR y por la macro ASSERT es caso de que no se
 * cumpla su expresión.
 * @ingroup ERROR
 *
 * @details Imprime la función, fichero fuente y línea donde se produjo el error seguido del
 * mensaje descriptivo del error que se indicó en ERROR o ASSERT. A continuación el programa queda
 * en un bucle sin fin. Este comportamiento puede cambiarse modificando la función.
 *
 * @param[in] fichero   Nombre del fichero fuente donde se produjo el error.
 * @param[in] funcion   Nombre de la función donde se produjo el error.
 * @param[in] linea     Número de línea del fichero fuente donde produjo el error.
 * @param[in] mensaje   Mensaje descriptivo del error.
 */
void parar_con_error(const char *ptr_fichero, const char *ptr_funcion, const uint32_t linea,
                     const char *ptr_mensaje) {

  uint32_t i;

  // Deshabilitar las interrupciones
  __disable_irq();

  // Configurar la pantalla LCD si está siendo utilizada
  #ifdef EA_GLCD
    glcd_xy_texto(0, 0);
    glcd_color_texto(BLANCO);
    glcd_fondo_texto(NEGRO);
    glcd_seleccionar_fuente(FUENTE8X16);
    glcd_borrar(NEGRO);
  #endif

  // Imprimir la información del error mediante la salida por defecto
  printf("Error: %s\n", ptr_mensaje);
  printf("En funcion: %s\n", ptr_funcion);
  printf("Fichero: %s\n", ptr_fichero);
  printf("Linea: %u", linea);

  // Dejar al programa encerrado aquí
  LPC_GPIO1->DIR |= (1u << 5);

  while (1) {
    LPC_GPIO1->CLR = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
    LPC_GPIO1->SET = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
  }
}

/**
 * @brief   Manejador de la excepción "Hardware Fault".
 * @ingroup ERROR
 *
 * @details Al producirse este tipo de excepción se enciende un led rojo de forma intermitente
 * en la tarjeta Embedded Artist Developer's Kit para indicarlo dado que el sistema deja de
 * responder.
 */
void HardFault_Handler(void) {

  uint32_t i;

  // Deshabilitar las interrupciones
  __disable_irq();

  // Dejar al programa encerrado aquí
  LPC_GPIO1->DIR |= (1u << 5);

  while (1) {
    LPC_GPIO1->CLR = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
    LPC_GPIO1->SET = (1u << 5);
    for (i = 0; i < 5000000; i++) { __NOP(); }
  }
}
