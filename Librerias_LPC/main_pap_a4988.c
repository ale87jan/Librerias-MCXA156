#include <LPC407x_8x_177x_8x.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "glcd.h"
#include "gpio_lpc40xx.h"
#include "joystick.h"
#include "pap_a4988.h"

// Prototipos de funciones en main.c

int main(void) {

  glcd_inicializar();
  glcd_borrar(NEGRO);
  glcd_printf("Iniciando motor...\n");
  motor_inicializar(PUERTO1, PIN7, PUERTO1, PIN2, PUERTO1, PIN5);
  glcd_printf("Estado: OFF\n");
  glcd_printf("Dir: \n");


  while (1) {
    uint8_t c = joystick_leer();
    if (c == JOYSTICK_ARRIBA) {
      motor_iniciar_giro(DIR_ARRIBA);
      glcd_xy_texto(8*16,32);
      glcd_printf("ON  ");
      glcd_xy_texto(5*16,2*32);
      glcd_printf("Arriba   ");
    }else if (c == JOYSTICK_ABAJO) {
      motor_iniciar_giro(DIR_ABAJO);
      glcd_xy_texto(8*16,32);
      glcd_printf("ON  ");
      glcd_xy_texto(5*16,2*32);
      glcd_printf("Abajo     ");
    }else if (c == JOYSTICK_CENTRO) {
      motor_detener_giro();
      glcd_xy_texto(8*16,32);
      glcd_printf("OFF ");
      glcd_xy_texto(5*16,2*32);
      glcd_printf("            ");
    }else if (c == JOYSTICK_DERECHA) {
      motor_detener_giro();
      motor_bloqueo(MOTOR_BLOQUEADO);
      glcd_xy_texto(8*16,32);
      glcd_printf("OFF ");
      glcd_xy_texto(5*16,2*32);
      glcd_printf("            ");
    }else if (c == JOYSTICK_IZQUIERDA) {
      motor_detener_giro();
      motor_bloqueo(MOTOR_DESBLOQUEADO);
      glcd_xy_texto(8*16,32);
      glcd_printf("OFF ");
      glcd_xy_texto(5*16,2*32);
      glcd_printf("            ");
    }
  }
}
