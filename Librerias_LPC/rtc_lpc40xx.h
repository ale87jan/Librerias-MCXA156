/**
 * @file    rtc_lpc40xx.h
 * @brief   Funciones de acceso al RTC del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es
 * @date    2026
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef RTC_LPC40XX_H
#define RTC_LPC40XX_H

#include "tipos.h"

/**
 * @brief Enumeración para definir los tipos de interrupciones disponibles.
 */
enum rtc_interrupciones {
  RTC_INT_SEG      = (1u << 0),   //!< Interrupción cada segundo.
  RTC_INT_MIN      = (1u << 1),   //!< Interrupción cada minuto.
  RTC_INT_HORA     = (1u << 2),   //!< Interrupción cada hora.
  RTC_INT_DIA_MES  = (1u << 3),   //!< Interrupción cada día del mes.
  RTC_INT_DIA_SEM  = (1u << 4),   //!< Interrupción cada día de la semana.
  RTC_INT_DIA_ANNO = (1u << 5),   //!< Interrupción cada día del año.
  RTC_INT_MES      = (1u << 6),   //!< Interrupción cada mes.
  RTC_INT_ANNO     = (1u << 7)    //!< Interrupción cada año.
};

/**
 * @brief Enumeración para definir las máscaras aplicables a la alarma. Se ignoran aquellos valores
 * con su bit activo.
 */
enum rtc_alarma_mascara {
  RTC_ALARMA_SEG      = (1u << 0),   //!< Ignora los segundos.
  RTC_ALARMA_MIN      = (1u << 1),   //!< Ignora los minutos.
  RTC_ALARMA_HORA     = (1u << 2),   //!< Ignora la hora.
  RTC_ALARMA_DIA_MES  = (1u << 3),   //!< Ignora el día del mes.
  RTC_ALARMA_DIA_SEM  = (1u << 4),   //!< Ignora el día de la semana.
  RTC_ALARMA_DIA_ANNO = (1u << 5),   //!< Ignora el día del año.
  RTC_ALARMA_MES      = (1u << 6),   //!< Ignora el mes.
  RTC_ALARMA_ANNO     = (1u << 7)    //!< Ignora el año.
};

/**
 * @brief Estructura auxiliar para manejar la fecha y hora de manera conveniente.
 */
typedef struct {
  uint8_t   segundos;     //!< Segundos (6 bits).
  uint8_t   minutos;      //!< Minutos (6 bits).
  uint8_t   horas;        //!< Horas (5 bits).
  uint8_t   dia_mes;      //!< Día del mes (5 bits).
  uint8_t   dia_semana;   //!< Día de la semana (3 bits).
  uint16_t  dia_anno;     //!< Día del año (9 bits).
  uint8_t   mes;          //!< Mes (4 bits).
  uint16_t  anno;         //!< Año (12 bits).
} fecha_hora_t;

// ===== RTC - Funciones Públicas =====
/**
 * @brieg   Inicializa el RTC.
 * @ingroup RTC
 *
 * @details Activa la alimentación en el registro de alimentación de periféricos y activa el bit
 * Clock Enable del registro de control del RTC (CCR).
 */
void rtc_inicializar(void);

/**
 * @brief   Ajusta los parámetros de hora del RTC.
 * @ingroup RTC
 *
 * @param[in]   fecha_hora_actual   Puntero a la estructura de fecha_hora con la hora actual.
 */
void rtc_ajustar_hora(fecha_hora_t fecha_hora_actual);

/**
 * @brief   Ajusta los parámetros de la fecha del RTC.
 * @ingroup RTC
 *
 * @param[in]   fecha_hora_actual   Puntero a la estructura de fecha_hora con la fecha actual.
 */
void rtc_ajustar_fecha(fecha_hora_t fecha_hora_actual);

/**
 * @brief   Ajusta las interrupciones por incremento de las unidades de tiempo seleccionadas.
 * @ingroup RTC
 *
 * @param[in]   interrupciones_activas
 */
void rtc_ajustar_interrupciones(uint8_t interrupciones_activas);

/**
 * @brief   Ajusta la alarma a la fecha y hora indicadas.
 * @ingroup RTC
 *
 * @param[in]   fecha_hora_alarma   Puntero con la estructura de fecha_hora de la alarma.
 * @param[in]   ignorados           Campos de tiempo a ignorar para la alarma.
 */
void rtc_ajustar_alarma(fecha_hora_t fecha_hora_alarma, uint8_t ignorados);

/**
 * @brief   Lee la hora actual.
 * @ingroup RTC
 *
 * @param[out]   fecha_hora_actual  Puntero a la estructura de fecha_hora donde guardarla.
 */
void rtc_leer_hora(fecha_hora_t *fecha_hora_actual);

/**
 * @brief   Lee la fecha actual.
 * @ingroup RTC
 *
 * @param[out]   fecha_hora_actual  Puntero a la estructura de fecha_hora donde guardarla.
 */
void rtc_leer_fecha(fecha_hora_t *fecha_hora_actual);

/**
 * @brief   Lee las interrupciones por incremento activas en el RTC.
 * @ingroup RTC
 *
 * @return  Interrupciones activas.
 */
uint8_t rtc_leer_interrupciones(void);

/**
 * @brief   Lee la fecha y hora de la alarma configurada.
 * @ingroup RTC
 *
 * @param[out]   fecha_hora_alarma  Puntero a la estructura de fecha_hora donde guardar la alarma.
 * @param[out]   ignorados          Máscara de los campos ignorados para la alarma.
 */
void rtc_leer_alarma(fecha_hora_t *fecha_hora_alarma, uint8_t *ignorados);

#endif  // RTC_LPC40XX_H
