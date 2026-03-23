/**
 * @file    rtc_lpc40xx.c
 * @brief   Funciones para usar el RTC del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "rtc_lpc40xx.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

// ===== RTC - Funciones Públicas =====
void rtc_inicializar(void) {
  LPC_SC->PCONP |= (1u << 9);
  LPC_RTC->CCR = 1;
}

void rtc_ajustar_hora(fecha_hora_t fecha_hora_actual) {

  // Deshabilitar el avance del RTC mientras se ajusta la hora
  LPC_RTC->CCR &= ~1;
  
  LPC_RTC->SEC  = fecha_hora_actual.segundos;
  LPC_RTC->MIN  = fecha_hora_actual.minutos;
  LPC_RTC->HOUR = fecha_hora_actual.horas;
  
  // Volver a permitir que el RTC avance
  LPC_RTC->CCR |= 1;
}

void rtc_ajustar_fecha(fecha_hora_t fecha_hora_actual) {
  
  // Deshabilitar el avance del RTC mientras se ajusta la fecha
  LPC_RTC->CCR &= ~1;
  
  LPC_RTC->DOM   = fecha_hora_actual.dia_mes;
  LPC_RTC->MONTH = fecha_hora_actual.mes;
  LPC_RTC->YEAR  = fecha_hora_actual.anno;

  // Volver a permitir que el RTC avance
  LPC_RTC->CCR |= 1;
}

void rtc_ajustar_interrupciones(uint8_t interrupciones_activas) {

  LPC_RTC->CIIR = interrupciones_activas;

}

void rtc_ajustar_alarma(fecha_hora_t fecha_hora_alarma, uint8_t ignorados) {

  LPC_RTC->ALSEC  = fecha_hora_alarma.segundos;
  LPC_RTC->ALMIN  = fecha_hora_alarma.minutos;
  LPC_RTC->ALHOUR = fecha_hora_alarma.horas;
  LPC_RTC->ALDOM  = fecha_hora_alarma.dia_mes;
  LPC_RTC->ALDOW  = fecha_hora_alarma.dia_semana;
  LPC_RTC->ALDOY  = fecha_hora_alarma.dia_anno;
  LPC_RTC->ALMON  = fecha_hora_alarma.mes;
  LPC_RTC->ALYEAR = fecha_hora_alarma.anno;
  
  LPC_RTC->AMR = ignorados;
}

void rtc_leer_hora(fecha_hora_t *fecha_hora_actual) {

  uint32_t lecturahora = LPC_RTC->CTIME0;
  
  fecha_hora_actual->segundos =  lecturahora        & 0x3F;
  fecha_hora_actual->minutos  = (lecturahora >> 8)  & 0x3F;
  fecha_hora_actual->horas    = (lecturahora >> 16) & 0x1F;
}

void rtc_leer_fecha(fecha_hora_t *fecha_hora_actual) {

  uint32_t lecturafecha = LPC_RTC->CTIME1;
  
  fecha_hora_actual->dia_mes = lecturafecha         & 0x1F;
  fecha_hora_actual->mes     = (lecturafecha >> 8)  & 0x0F;
  fecha_hora_actual->anno    = (lecturafecha >> 16) & 0x0FFF;
  
  lecturafecha = LPC_RTC->CTIME0;
  
  fecha_hora_actual->dia_semana = (lecturafecha >> 24) & 0x07;
  
  lecturafecha = LPC_RTC->CTIME2;
  
  fecha_hora_actual->dia_anno = lecturafecha & 0x01FF;
}

uint8_t rtc_leer_interrupciones(void) {
  return LPC_RTC->CIIR & 0xFF;
}

void rtc_leer_alarma(fecha_hora_t *fecha_hora_alarma, uint8_t *ignorados) {

  fecha_hora_alarma->segundos   = LPC_RTC->ALSEC;
  fecha_hora_alarma->minutos    = LPC_RTC->ALMIN;
  fecha_hora_alarma->horas      = LPC_RTC->ALHOUR;
  fecha_hora_alarma->dia_mes    = LPC_RTC->ALDOM;
  fecha_hora_alarma->dia_semana = LPC_RTC->ALDOW;
  fecha_hora_alarma->dia_anno   = LPC_RTC->ALDOY;
  fecha_hora_alarma->mes        = LPC_RTC->ALMON;
  fecha_hora_alarma->anno       = LPC_RTC->ALYEAR;
  
  *ignorados = LPC_RTC->AMR;
}