/**
 * @file    main_uart.c
 * @brief   Programa principal de comunicación con un PC mediante la UART0 del LPC4088.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
#include "leds.h"
#include "uart_lpc40xx.h"

int main(void) {

  glcd_inicializar();
  leds_inicializar();
  timer_inicializar(TIMER0);

  /* Inicializar la UART0: 115200 baudios, datos de 8 bits, sin paridad y un bit de stop
   * Usar el pin P0[2] para TxD y el pin P0[3] para RxD. */
  uart_inicializar(UART0, UART_BAUDRATE_115200, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA,
                   UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);

  while (1) {
    // Leer el joystick y enviar un carácter según la dirección pulsada
    // - JOYSTICK_ARRIBA => 'A'
    // - JOYSTICK_ABAJO => 'B'
    // - JOYSTICK_IZQUIERDA => 'I'
    // - JOYSTICK_DERECHA => 'D'
    // - JOYSTICK_CENTRO => 'C'
    switch (joystick_leer()) {
      case JOYSTICK_ARRIBA:
        glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "ARRIBA    \n");
        uart_transmitir_dato(UART0, 'A');
        break;

      case JOYSTICK_ABAJO:
        glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "ABAJO    \n");
        uart_transmitir_dato(UART0, 'B');
        break;

      case JOYSTICK_IZQUIERDA:
        glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "IZQUIERDA\n");
        uart_transmitir_dato(UART0, 'I');
        break;

      case JOYSTICK_DERECHA:
        glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "DERECHA  \n");
        uart_transmitir_dato(UART0, 'D');
        break;

      case JOYSTICK_CENTRO:
        glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "CENTRO   \n");
        uart_transmitir_dato(UART0, 'C');
        break;

      default:
        break;
    }

    /* Leer si se ha recibido algún dato en la UART y, en el caso de recibir un número del 1 al 4,
     * invertir el LED correspondiente.
     */
    if (uart_hay_dato_disponible(UART0)) {
      switch ((char) uart_leer_dato(UART0)) {
        case '1':
          leds_invertir(LED1);
          break;
        case '2':
          leds_invertir(LED2);
          break;
        case '3':
          leds_invertir(LED3);
          break;
        case '4':
          leds_invertir(LED4);
          break;
        default:
          break;
      }
    }

    timer_retardo_ms(TIMER0, 200);
  }
}
