/**
 * @file    main_pwm_led_rgb.c
 * @brief   Ejemplo de manejo de un led RGB mediante PWM.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 3.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
#include "pwm_led_rgb.h"

int main(void) {

  uint8_t r = 0, g = 0, b = 0;
  uint32_t color;
  
  // Inicializar pantalla LCD y Timer0
  glcd_inicializar();
  timer_inicializar(TIMER0);

  //Inicializar la generación PWM con todos los colores inicialmente apagados.
  led_rgb_inicializar();

  //Recorrer colores
  while (1) {
    for (; r < 255; r += 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; g < 255; g += 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; r >0; r -= 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; b < 255; b += 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; g > 0; g -= 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; r < 255; r += 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; g < 255; g += 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
    for (; (r > 0) && (g > 0) && (b > 0); r -= 5, g -= 5, b -= 5) {
      color= LED_RGB(r, g, b);
      led_rgb_ajustar_color(color);
      timer_retardo_ms(TIMER0, 25);
    }
  }
}