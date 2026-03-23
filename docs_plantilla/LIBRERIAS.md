<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

<!-- markdownlint-disable MD024 -->

# Librerías MCXA156

## Contenido

- [Introducción](#introducción)
- [Librerías de Periféricos](#librerías-de-periféricos)
- [Librerías Gráficas](#librerías-gráficas)
- [Librerías de Sensores](#librerías-de-sensores)
- [Librerías de Actuadores](#librerías-de-actuadores)
- [Librerías de Juegos](#librerías-de-juegos)
- [Utilidades y Tipos](#utilidades-y-tipos)

## Introducción

Este documento describe todas las librerías disponibles en el repositorio
Librerias-MCXA156. Las librerías están organizadas por funcionalidad y
proporcionan una interfaz de alto nivel para acceder a los periféricos del
microcontrolador NXP MCXA156 (ARM Cortex-M33) y componentes externos de la
placa FRDM-MCXA156.

### Convenciones

- Las funciones públicas están documentadas con comentarios Doxygen
- Los nombres de las librerías de periféricos siguen el patrón `<periferico>_mcxa15x`
- Las funciones siguen el patrón `modulo_funcion_descriptiva()` (snake_case)
- Los archivos de cabecera (.h) contienen la documentación de la API
- Los ejemplos de uso están en archivos `main_<nombre>.c`

---

## Librerías de Periféricos

### GPIO (gpio_mcxa15x)

**Archivos:** `gpio_mcxa15x.h`, `gpio_mcxa15x.c`

Control de entradas y salidas digitales de propósito general.

#### Características

<!-- TODO: Completar con las características específicas del GPIO del MCXA156 -->

- Configuración individual de pines como entrada o salida
- Lectura y escritura de pines individuales o puertos completos
- Soporte para interrupciones por flanco
- Configuración de pull-up/pull-down mediante PORT

#### Funciones Principales

```c
// Configuración
void gpio_ajustar_dir(uint8_t puerto, uint8_t pin, uint8_t dir);
void gpio_escribir_pin(uint8_t puerto, uint8_t pin, uint8_t valor);
uint8_t gpio_leer_pin(uint8_t puerto, uint8_t pin);

// Interrupciones
// TODO: Definir API de interrupciones GPIO
```

#### Ejemplo de Uso

Ver `main_base.c` para ejemplos con LEDs y botones.

---

### UART (uart_mcxa15x)

**Archivos:** `uart_mcxa15x.h`, `uart_mcxa15x.c`

Comunicación serie asíncrona full-duplex mediante LPUART.

#### Características

<!-- TODO: Completar con las características específicas del LPUART del MCXA156 -->

- Soporte para múltiples instancias LPUART
- Baudrates configurables
- Configuración de bits de datos, paridad y bits de stop
- FIFOs de transmisión y recepción
- Interrupciones por RX, TX, error

#### Funciones Principales

```c
// Inicialización
void uart_inicializar(uint8_t instancia, uint32_t baudrate);

// Transmisión/Recepción
void uart_enviar_byte(uint8_t instancia, uint8_t dato);
uint8_t uart_recibir_byte(uint8_t instancia);
void uart_enviar_cadena(uint8_t instancia, const char *ptr_cadena);

// Estado
// TODO: Definir funciones de estado
```

#### Ejemplo de Uso

Ver `main_uart.c` para comunicación con terminal serie.

---

### ADC (adc_mcxa15x)

**Archivos:** `adc_mcxa15x.h`, `adc_mcxa15x.c`

Conversión analógico-digital mediante LPADC.

#### Características

<!-- TODO: Completar con las características específicas del LPADC del MCXA156 -->

- Resolución configurable (hasta 16 bits)
- Múltiples canales de entrada
- Voltaje de referencia: 3.3V
- Modo de conversión por hardware trigger o software trigger

#### Funciones Principales

```c
// Inicialización
void adc_inicializar(void);

// Lectura
uint16_t adc_leer_canal(uint8_t canal);

// Conversión a voltaje
// TODO: Definir función de conversión a voltaje
```

#### Ejemplo de Uso

<!-- TODO: Añadir referencia a ejemplos -->

---

### DAC (dac_mcxa15x)

**Archivos:** `dac_mcxa15x.h`, `dac_mcxa15x.c`

Conversión digital-analógico.

#### Características

<!-- TODO: Completar con las características específicas del DAC del MCXA156 -->

- Salida de voltaje 0-3.3V
- Resolución de 12 bits

#### Funciones Principales

```c
// TODO: Definir API del DAC
void dac_inicializar(void);
void dac_escribir_valor(uint16_t valor);
```

---

### PWM (pwm_mcxa15x)

**Archivos:** `pwm_mcxa15x.h`, `pwm_mcxa15x.c`

Generación de señales PWM mediante CTimer/FlexPWM.

#### Características

<!-- TODO: Completar con las características específicas del PWM del MCXA156 -->

- Frecuencia configurable
- Duty cycle de 0-100%
- Múltiples canales

#### Funciones Principales

```c
// TODO: Definir API del PWM
void pwm_inicializar(uint8_t canal, uint32_t frecuencia);
void pwm_ajustar_ciclo(uint8_t canal, uint8_t porcentaje);
```

---

### SPI (spi_mcxa15x)

**Archivos:** `spi_mcxa15x.h`, `spi_mcxa15x.c`

Comunicación serie síncrona mediante LPSPI.

#### Características

<!-- TODO: Completar con las características específicas del LPSPI del MCXA156 -->

- Múltiples instancias LPSPI
- Modo maestro y esclavo
- Velocidad configurable
- Modos SPI 0-3 (CPOL/CPHA)

#### Funciones Principales

```c
// Inicialización
void spi_inicializar(uint8_t instancia, uint32_t frecuencia);

// Transferencia
uint8_t spi_transferir(uint8_t instancia, uint8_t dato);
void spi_enviar_datos(uint8_t instancia, const uint8_t *ptr_datos, uint32_t longitud);

// TODO: Completar API
```

---

### I2C (i2c_mcxa15x)

**Archivos:** `i2c_mcxa15x.h`, `i2c_mcxa15x.c`

Bus de comunicación serie de 2 hilos mediante LPI2C.

#### Características

<!-- TODO: Completar con las características específicas del LPI2C del MCXA156 -->

- Múltiples instancias LPI2C
- Modo maestro y esclavo
- Velocidad estándar (100 kHz) y rápida (400 kHz)
- Direccionamiento de 7 y 10 bits

#### Funciones Principales

```c
// Inicialización
void i2c_inicializar(uint8_t instancia, uint32_t frecuencia);

// Transferencia
bool i2c_escribir(uint8_t instancia, uint8_t direccion,
                  const uint8_t *ptr_datos, uint32_t longitud);
bool i2c_leer(uint8_t instancia, uint8_t direccion,
              uint8_t *ptr_datos, uint32_t longitud);
```

---

### RTC (rtc_mcxa15x)

**Archivos:** `rtc_mcxa15x.h`, `rtc_mcxa15x.c`

Reloj de tiempo real.

#### Características

<!-- TODO: Completar con las características específicas del RTC del MCXA156 -->

- Reloj completo: año, mes, día, hora, minuto, segundo
- Alarma configurable
- Oscilador de 32.768 kHz

#### Estructuras

```c
typedef struct {
    uint8_t  segundo;    // 0-59
    uint8_t  minuto;     // 0-59
    uint8_t  hora;       // 0-23
    uint8_t  dia;        // 1-31
    uint8_t  mes;        // 1-12
    uint16_t ano;        // Año completo
    uint8_t  dia_semana; // 0-6 (0=Domingo)
} rtc_fecha_hora_t;
```

#### Funciones Principales

```c
// Configuración
void rtc_inicializar(void);
void rtc_ajustar_hora(uint8_t hora, uint8_t minuto, uint8_t segundo);
void rtc_ajustar_fecha(uint16_t ano, uint8_t mes, uint8_t dia);

// Lectura
rtc_fecha_hora_t rtc_obtener_fecha_hora(void);
```

---

### Timer (timer_mcxa15x)

**Archivos:** `timer_mcxa15x.h`, `timer_mcxa15x.c`

Temporizadores de propósito general mediante CTimer.

#### Características

<!-- TODO: Completar con las características específicas de los CTimers del MCXA156 -->

- Múltiples temporizadores CTimer de 32 bits
- Modo contador/temporizador
- Canales de captura y comparación
- Generación de interrupciones

#### Funciones Principales

```c
// Inicialización
void timer_inicializar(uint8_t instancia, uint32_t prescaler);
void timer_iniciar(uint8_t instancia);
void timer_detener(uint8_t instancia);

// Lectura
uint32_t timer_obtener_valor(uint8_t instancia);
```

---

### PORT (port_mcxa15x)

**Archivos:** `port_mcxa15x.h`, `port_mcxa15x.c`

Configuración del multiplexado de pines (equivalente a IOCON del LPC4088).

#### Características

<!-- TODO: Completar con las características específicas del PORT del MCXA156 -->

- Selección de función alternativa de cada pin (mux)
- Configuración de pull-up/pull-down
- Configuración de slew rate y drive strength

#### Funciones Principales

```c
// Configuración de función
void port_ajustar_mux(uint8_t puerto, uint8_t pin, uint8_t funcion);

// Configuración de modo
void port_ajustar_modo(uint8_t puerto, uint8_t pin, uint8_t modo);
```

---

## Librerías Gráficas

### GLCD (glcd)

**Archivos:** `glcd.h`, `glcd.c`

Librería gráfica para la pantalla LCD-PAR-S035 (3.5", SPI).

#### Características

<!-- TODO: Completar con las características de la LCD-PAR-S035 -->

- Resolución: 480x320 píxeles
- Profundidad de color: 16 bits (RGB565)
- Interfaz SPI
- Funciones de dibujo primitivas
- Soporte para fuentes de texto

#### Funciones de Dibujo

```c
// Inicialización
void glcd_inicializar(void);
void glcd_limpiar(uint16_t color);

// Píxeles y líneas
void glcd_dibujar_pixel(uint16_t x, uint16_t y, uint16_t color);
void glcd_dibujar_linea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                        uint16_t color);

// Formas
void glcd_dibujar_rectangulo(uint16_t x, uint16_t y, uint16_t ancho,
                             uint16_t alto, uint16_t color);
void glcd_rellenar_rectangulo(uint16_t x, uint16_t y, uint16_t ancho,
                              uint16_t alto, uint16_t color);
void glcd_dibujar_circulo(uint16_t x, uint16_t y, uint16_t radio,
                          uint16_t color);

// Texto
void glcd_escribir_caracter(uint16_t x, uint16_t y, char caracter,
                            uint16_t color_texto, uint16_t color_fondo);
void glcd_escribir_cadena(uint16_t x, uint16_t y, const char *ptr_cadena,
                          uint16_t color_texto, uint16_t color_fondo);
```

#### Colores Predefinidos

```c
#define GLCD_COLOR_NEGRO    0x0000
#define GLCD_COLOR_BLANCO   0xFFFF
#define GLCD_COLOR_ROJO     0xF800
#define GLCD_COLOR_VERDE    0x07E0
#define GLCD_COLOR_AZUL     0x001F
#define GLCD_COLOR_AMARILLO 0xFFE0
#define GLCD_COLOR_CYAN     0x07FF
#define GLCD_COLOR_MAGENTA  0xF81F
```

#### Fuentes Disponibles

<!-- TODO: Definir fuentes disponibles -->

---

## Librerías de Sensores

<!-- TODO: Definir sensores disponibles en la FRDM-MCXA156 / placa de expansión -->

### Plantilla de sensor

**Archivos:** `sensor_mcxa15x.h`, `sensor_mcxa15x.c`

```c
void sensor_inicializar(void);
// TODO: Definir API según los sensores disponibles
```

---

## Librerías de Actuadores

### LEDs (gpio_leds)

**Archivos:** `gpio_leds.h`, `gpio_leds.c`

Control de los LEDs integrados en la placa FRDM-MCXA156.

#### Características

<!-- TODO: Verificar cantidad y pines de LEDs en la FRDM-MCXA156 -->

- Control individual de cada LED
- Estados: encendido, apagado, toggle

#### Funciones Principales

```c
void gpio_leds_inicializar(void);
void gpio_leds_encender(uint8_t led);
void gpio_leds_apagar(uint8_t led);
void gpio_leds_conmutar(uint8_t led);
```

---

### LED RGB (gpio_led_rgb)

**Archivos:** `gpio_led_rgb.h`, `gpio_led_rgb.c`

Control del LED RGB integrado en la placa FRDM-MCXA156 mediante PWM.

#### Funciones Principales

```c
void gpio_led_rgb_inicializar(void);
void gpio_led_rgb_ajustar_color(uint8_t rojo, uint8_t verde, uint8_t azul);
```

---

## Librerías de Juegos

### Joystick (gpio_joystick)

**Archivos:** `gpio_joystick.h`, `gpio_joystick.c`

Lectura del joystick de la placa de expansión.

#### Funciones Principales

```c
void gpio_joystick_inicializar(void);
uint8_t gpio_joystick_leer(void);
```

#### Constantes

```c
#define JOYSTICK_CENTRO     0x00
#define JOYSTICK_ARRIBA     0x01
#define JOYSTICK_ABAJO      0x02
#define JOYSTICK_IZQUIERDA  0x04
#define JOYSTICK_DERECHA    0x08
#define JOYSTICK_SIN_PULSAR 0x10
```

---

### Tetris (Proyecto Completo)

**Archivos:** `bloque.h/.c`, `cubeta.h/.c`, `piezas.h/.c`, `juego.h/.c`,
`marcador.h/.c`, `menu.h/.c`

Implementación completa del juego Tetris adaptada a la LCD-PAR-S035.

<!-- TODO: Adaptar estructuras y API del Tetris al MCXA156 -->

---

## Utilidades y Tipos

### Tipos (tipos.h)

**Archivo:** `tipos.h`

Definiciones de tipos y macros de utilidad compartidas por todas las librerías.

<!-- TODO: Definir si se mantiene tipos.h o se usa <stdint.h> + <stdbool.h> directamente -->

#### Macros de Manipulación de Bits

```c
#define _BIT(n)              (1u << (n))
#define BIT_READ(reg, bit)   (((reg) >> (bit)) & 1u)
#define BIT_SET(reg, bit)    ((reg) |= _BIT(bit))
#define BIT_CLEAR(reg, bit)  ((reg) &= ~_BIT(bit))
```

---

## Dependencias entre Librerías

```text
glcd
├── spi_mcxa15x
└── tipos

gpio_mcxa15x
├── port_mcxa15x
└── tipos

uart_mcxa15x
├── port_mcxa15x
└── tipos

adc_mcxa15x
├── port_mcxa15x
└── tipos

spi_mcxa15x
├── port_mcxa15x
└── tipos

i2c_mcxa15x
├── port_mcxa15x
└── tipos

gpio_leds
├── gpio_mcxa15x
└── tipos

gpio_led_rgb
├── pwm_mcxa15x
└── tipos

gpio_joystick
├── adc_mcxa15x
└── tipos

tetris (proyecto completo)
├── glcd
├── gpio_joystick
├── timer_mcxa15x
├── bloque
├── cubeta
├── piezas
├── juego
├── marcador
└── menu
```

## Estructura de Proyectos Keil

Cada proyecto Keil (`.uvprojx`) incluye:

- Archivos fuente necesarios
- Configuración del microcontrolador MCXA156
- Opciones de compilación (ARM Compiler 6)
- Configuración de depuración
- Scripts de enlazado (scatter files)

## Generación de Documentación

### Doxygen

El proyecto incluye configuración de Doxygen para generar documentación HTML.

```bash
doxygen Doxyfile
```

La documentación se generará en `docs/html/index.html`.

## Convenciones de Código

### Nomenclatura

- **Funciones:** `modulo_funcion_descriptiva()` (snake_case)
- **Variables locales:** `nombre_variable` (snake_case)
- **Variables globales:** `g_nombre` (snake_case con prefijo `g_`)
- **Constantes/Macros:** `NOMBRE_CONSTANTE` (UPPER_CASE)
- **Tipos:** `nombre_t` (snake_case con sufijo `_t`)
- **Enums:** tipo `nombre_t`, valores `kNombreValor` (CamelCase con prefijo `k`)

### Comentarios Doxygen

```c
/**
 * @brief   Descripción breve de la función.
 *
 * @param[in]  parametro1  Descripción del parámetro de entrada.
 * @param[out] parametro2  Descripción del parámetro de salida.
 * @retval     Descripción del valor de retorno.
 *
 * @note    Notas adicionales.
 */
```

## Referencias

Para más información sobre el uso de las librerías:

- [Ejemplos de Código](proyectos/EJEMPLOS.md) - Proyectos de ejemplo
- [Documentación de Hardware](HARDWARE.md) - Especificaciones del hardware
- [Guía de Instalación](INSTALACION.md) - Configuración del entorno

Para la documentación completa de la API, genera la documentación Doxygen o
consulta los archivos de cabecera (`.h`) de cada librería.

---

**Última actualización:** 2026
