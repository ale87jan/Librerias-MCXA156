/**
 * @file    menu.h
 * @brief   Menú principal y funciones de configuración de los TIMERs para el bucle de juego y
 * detección de pulsaciones en el joystick.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef MENU_H
#define MENU_H

#include "tipos.h"

// ===== Juego - Constantes Públicas =====
/**
 * @brief   Constante para identificar el joystick como inactivo.
 * @ingroup Menu
 */
#define JOYSTICK_INACTIVO 0xA5

// ===== Menu - Funciones Públicas =====
void menu(void);
void configurar_bucle_juego(void);
void configurar_lectura_pulsaciones(void);
uint8_t leer_pulsacion(void);

#endif  // MENU_H
