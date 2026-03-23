/**
 * @file  main_lm75b.c
 * @brief Programa principal de acceso a un sensor de temperatura LM75B mediante la interfaz I2C0.
 *
 * @author    Alejandro Lara Doña - alejandro.lara@uca.es
 * @date      2025
 * @version   1.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdio.h>
#include "glcd.h"
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "i2c_lpc40xx.h"
#include "uart_lpc40xx.h"
#include "lm75b_lpc40xx.h"

int main(void) {

  float32_t grados;
  char buffer[20];
  
  glcd_inicializar();
  lm75b_inicializar(I2C0,             // Interfaz I2C del LPC40xx a utilizar
                    100000,           // Frecuencia SCL
                    PUERTO0, PIN27,   // Puerto y pin SDA
                    PUERTO0, PIN28,   // Puerto y pin SCL
                    LM75B_DIR_I2C);   // Dirección I2C del LM75B
  
  /* ===== Ejercicio 2 =====
   * Inicializar la UART0: 115200 baudios, datos de 8 bits, sin paridad y un bit de stop
   * Usar el pin P0[2] para TxD y el pin P0[3] para RxD.
   */
  uart_inicializar(UART0, UART_BAUDRATE_115200, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA,
                   UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);

  timer_inicializar(TIMER0);
  timer_iniciar_ciclos_ms(TIMER0, 1000);

  while (1) {
    grados = lm75b_leer_temperatura();
    
    snprintf(buffer, 20, "Temp(C): %3.3f\n", grados);
    glcd_xprintf(0, 0, BLANCO, NEGRO, FUENTE16X32, "%s", buffer);
    uart_transmitir_cadena(UART0, buffer);
    
    timer_esperar_fin_ciclo(TIMER0);
  }
}
