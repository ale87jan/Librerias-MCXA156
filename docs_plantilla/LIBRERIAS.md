<!-- LICENSE INFORMATION
Copyright (C) 2025 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

<!-- markdownlint-disable MD024 -->

# Librerías LPC4088

## 📚 Contenido

- [Introducción](#introducción)
- [Librerías de Periféricos](#librerías-de-periféricos)
- [Librerías Gráficas](#librerías-gráficas)
- [Librerías de Sensores](#librerías-de-sensores)
- [Librerías de Actuadores](#librerías-de-actuadores)
- [Librerías de Juegos](#librerías-de-juegos)
- [Utilidades y Tipos](#utilidades-y-tipos)

## Introducción

Este documento describe todas las librerías disponibles en el repositorio LPC4088-Documentacion. Las librerías están organizadas por funcionalidad y proporcionan una interfaz de alto nivel para acceder a los periféricos del microcontrolador y componentes externos.

### Convenciones

- Las funciones públicas están documentadas con comentarios Doxygen
- Los nombres de las librerías de periféricos siguen el patrón `<periferico>_lpc40xx`
- Los archivos de cabecera (.h) contienen la documentación de la API
- Los ejemplos de uso están en archivos `main_<nombre>.c`

## Librerías de Periféricos

### 🔌 GPIO (gpio_lpc40xx)

**Archivos:** `gpio_lpc40xx.h`, `gpio_lpc40xx.c`

Control de entradas y salidas digitales de propósito general.

#### Características

- Configuración individual de pines como entrada o salida
- Lectura y escritura de pines individuales o puertos completos
- Soporte para interrupciones por flanco o nivel
- Configuración de pull-up/pull-down
- Acceso directo a registros para operaciones rápidas

#### Funciones Principales

```c
// Configuración
void GPIO_SetDir(LPC_GPIO_TypeDef *gpio, uint32_t pin, uint32_t dir);
void GPIO_SetValue(LPC_GPIO_TypeDef *gpio, uint32_t pin);
void GPIO_ClearValue(LPC_GPIO_TypeDef *gpio, uint32_t pin);
uint32_t GPIO_ReadValue(LPC_GPIO_TypeDef *gpio, uint32_t pin);

// Interrupciones
void GPIO_IntConfig(LPC_GPIO_TypeDef *gpio, uint32_t pin, uint32_t mode);
void GPIO_IntEnable(LPC_GPIO_TypeDef *gpio, uint32_t pin);
```

#### Ejemplo de Uso

Ver `main_base.c` para ejemplos con LEDs y botones.

---

### 📡 UART (uart_lpc40xx)

**Archivos:** `uart_lpc40xx.h`, `uart_lpc40xx.c`

Comunicación serie asíncrona full-duplex.

#### Características

- Soporte para UART0, UART1, UART2, UART3
- Baudrates configurables (1200 a 115200 bps típicos)
- Configuración de bits de datos (5-8 bits)
- Paridad: ninguna, par, impar
- Bits de stop: 1 o 2
- FIFOs de transmisión y recepción (16 bytes)
- Interrupciones por RX, TX, error

#### Funciones Principales

```c
// Inicialización
void UART_Init(LPC_UART_TypeDef *uart, uint32_t baudrate);
void UART_ConfigDataBits(LPC_UART_TypeDef *uart, UART_DataBits_t databits);
void UART_ConfigParity(LPC_UART_TypeDef *uart, UART_Parity_t parity);

// Transmisión/Recepción
void UART_SendByte(LPC_UART_TypeDef *uart, uint8_t data);
uint8_t UART_ReceiveByte(LPC_UART_TypeDef *uart);
void UART_SendString(LPC_UART_TypeDef *uart, const char *str);

// Estado
bool_t UART_CheckBusy(LPC_UART_TypeDef *uart);
```

#### Ejemplo de Uso

Ver `main_uart.c` para comunicación con terminal serie.

---

### 🔄 ADC (adc_lpc40xx)

**Archivos:** `adc_lpc40xx.h`, `adc_lpc40xx.c`

Conversión analógico-digital de 12 bits.

#### Características

- 8 canales de entrada (ADC0.0 a ADC0.7)
- Resolución de 12 bits (0-4095)
- Velocidad de hasta 400 kSPS
- Voltaje de referencia: 3.3V
- Modo burst para conversiones continuas
- Interrupciones por conversión completa

#### Funciones Principales

```c
// Inicialización
void ADC_Init(void);
void ADC_ChannelConfig(uint8_t channel, bool_t enable);

// Lectura
uint16_t ADC_Read(uint8_t channel);
void ADC_StartConversion(uint8_t channel);
bool_t ADC_IsConversionDone(uint8_t channel);
uint16_t ADC_GetData(uint8_t channel);

// Conversión a voltaje
float ADC_ToVoltage(uint16_t adc_value);
```

#### Ejemplo de Uso

Ver `main_adc.c`, `main_ldr.c`, `main_ntc.c` para lecturas analógicas.

---

### 📊 DAC (No implementado aún)

**Archivos:** Pendiente

Conversión digital-analógico de 10 bits.

#### Características

- Salida de voltaje 0-3.3V
- Resolución de 10 bits (0-1023)
- Velocidad de hasta 400 kHz
- Ideal para generación de señales de audio

---

### 🔁 PWM (Integrado en otros periféricos)

El LPC4088 tiene capacidades PWM que se utilizan en:

- **LED RGB** (`led_rgb_lpc40xx`) - Control de color mediante PWM
- **Servo** (`servo_pwm`) - Control de servomotores

#### Características

- 6 salidas PWM independientes
- Frecuencia configurable
- Duty cycle de 0-100%
- Sincronización de canales

---

### 🔌 SPI (spi_lpc40xx)

**Archivos:** `spi_lpc40xx.h`, `spi_lpc40xx.c`

Comunicación serie síncrona maestro/esclavo.

#### Características

- 3 interfaces SSP (SSP0, SSP1, SSP2)
- Modo maestro y esclavo
- Velocidad configurable (hasta 25 MHz)
- Modos SPI 0-3 (CPOL/CPHA)
- Tamaño de datos: 4-16 bits
- FIFOs de 8 elementos

#### Funciones Principales

```c
// Inicialización
void SPI_Init(LPC_SSP_TypeDef *ssp, uint32_t clock_rate);
void SPI_ConfigClockPolarity(LPC_SSP_TypeDef *ssp, uint8_t polarity);
void SPI_ConfigClockPhase(LPC_SSP_TypeDef *ssp, uint8_t phase);

// Transferencia
uint16_t SPI_Transfer(LPC_SSP_TypeDef *ssp, uint16_t data);
void SPI_SendData(LPC_SSP_TypeDef *ssp, uint16_t data);
uint16_t SPI_ReceiveData(LPC_SSP_TypeDef *ssp);
```

#### Ejemplo de Uso

Ver `main_spi.c` (si está disponible) o `99.7_RFID` para uso con módulos SPI.

---

### 🔗 I2C (i2c_lpc40xx)

**Archivos:** `i2c_lpc40xx.h`, `i2c_lpc40xx.c`

Bus de comunicación serie de 2 hilos.

#### Características

- 3 interfaces I2C (I2C0, I2C1, I2C2)
- Modo maestro y esclavo
- Velocidad estándar (100 kHz) y rápida (400 kHz)
- Direccionamiento de 7 y 10 bits
- Reconocimiento de dirección multiple

#### Funciones Principales

```c
// Inicialización
void I2C_Init(LPC_I2C_TypeDef *i2c, uint32_t clock_rate);

// Transferencia
void I2C_Start(LPC_I2C_TypeDef *i2c);
void I2C_Stop(LPC_I2C_TypeDef *i2c);
void I2C_SendByte(LPC_I2C_TypeDef *i2c, uint8_t data);
uint8_t I2C_ReceiveByte(LPC_I2C_TypeDef *i2c, bool_t ack);

// Alto nivel
bool_t I2C_Write(LPC_I2C_TypeDef *i2c, uint8_t addr, uint8_t *data, uint32_t len);
bool_t I2C_Read(LPC_I2C_TypeDef *i2c, uint8_t addr, uint8_t *data, uint32_t len);
```

#### Ejemplo de Uso

Ver `main_lm75b.c` para lectura de sensor I2C.

---

### ⏰ RTC (rtc_lpc40xx)

**Archivos:** `rtc_lpc40xx.h`, `rtc_lpc40xx.c`

Reloj de tiempo real con alarma.

#### Características

- Reloj completo: año, mes, día, hora, minuto, segundo
- Calendario automático (incluyendo años bisiestos)
- Alarma configurable
- Interrupciones por incremento de tiempo
- Oscilador independiente de 32.768 kHz
- Funciona en modos de bajo consumo

#### Estructuras

```c
typedef struct {
    uint8_t  segundo;    // 0-59
    uint8_t  minuto;     // 0-59
    uint8_t  hora;       // 0-23
    uint8_t  dia;        // 1-31
    uint8_t  mes;        // 1-12
    uint16_t ano;        // 0-4095
    uint8_t  dia_semana; // 0-6 (0=Domingo)
} RTC_FechaHora_t;
```

#### Funciones Principales

```c
// Configuración
void RTC_Init(void);
void RTC_SetTime(uint8_t hora, uint8_t minuto, uint8_t segundo);
void RTC_SetDate(uint16_t ano, uint8_t mes, uint8_t dia);
void RTC_SetAlarm(RTC_FechaHora_t *alarma, uint32_t mascara);

// Lectura
RTC_FechaHora_t RTC_GetTime(void);
RTC_FechaHora_t RTC_GetDate(void);
```

#### Ejemplo de Uso

Ver `main_rtc.c` para reloj digital y alarmas.

---

### ⏱️ Timer (timer_lpc40xx)

**Archivos:** `timer_lpc40xx.h`, `timer_lpc40xx.c`

Temporizadores de propósito general.

#### Características

- 4 temporizadores de 32 bits (TIMER0-TIMER3)
- Modo contador/temporizador
- 4 canales de captura por timer
- 4 canales de comparación por timer
- Generación de interrupciones
- Prescaler configurable

#### Funciones Principales

```c
// Inicialización
void TIMER_Init(LPC_TIMER_TypeDef *timer, uint32_t prescaler);
void TIMER_Start(LPC_TIMER_TypeDef *timer);
void TIMER_Stop(LPC_TIMER_TypeDef *timer);
void TIMER_Reset(LPC_TIMER_TypeDef *timer);

// Comparación
void TIMER_SetMatch(LPC_TIMER_TypeDef *timer, uint8_t match, uint32_t value);
void TIMER_IntConfig(LPC_TIMER_TypeDef *timer, uint8_t match, bool_t enable);

// Lectura
uint32_t TIMER_GetValue(LPC_TIMER_TypeDef *timer);
```

#### Ejemplo de Uso

Ver `main_base.c` para temporización del bucle principal.

---

### 💾 EEPROM (eeprom_lpc40xx)

**Archivos:** `eeprom_lpc40xx.h`, `eeprom_lpc40xx.c`

Acceso a la EEPROM interna del LPC4088.

#### Características

- 4 KB de EEPROM interna
- Escritura y lectura por bytes o bloques
- Persistencia de datos sin alimentación
- Ciclos de escritura limitados (~100,000)

#### Funciones Principales

```c
// Lectura/Escritura
void EEPROM_WriteByte(uint16_t addr, uint8_t data);
uint8_t EEPROM_ReadByte(uint16_t addr);
void EEPROM_WriteBlock(uint16_t addr, uint8_t *data, uint16_t len);
void EEPROM_ReadBlock(uint16_t addr, uint8_t *data, uint16_t len);
```

#### Ejemplo de Uso

Ver `main_eeprom.c` para almacenamiento persistente.

---

### 🎛️ IOCON (iocon_lpc40xx)

**Archivos:** `iocon_lpc40xx.h`, `iocon_lpc40xx.c`

Configuración del multiplexado de pines.

#### Características

- Selección de función alternativa de cada pin
- Configuración de pull-up/pull-down/repetidor
- Configuración de modo analógico/digital
- Control de slew rate
- Control de inversión de entrada

#### Funciones Principales

```c
// Configuración de función
void IOCON_SetPinFunc(uint8_t port, uint8_t pin, uint8_t func);

// Configuración de modo
void IOCON_SetPinMode(uint8_t port, uint8_t pin, uint8_t mode);
```

---

## Librerías Gráficas

### 🖥️ GLCD (glcd)

**Archivos:** `glcd.h`, `glcd.c`, `sdram.h`, `sdram.c`

Librería gráfica para la pantalla LCD TFT de 4.3".

#### Características

- Resolución: 480x272 píxeles
- Profundidad de color: 16 bits (RGB565)
- Frame buffer en SDRAM externa (16 MB)
- Funciones de dibujo primitivas
- Soporte para fuentes de texto
- Aceleración por hardware del controlador LCD

#### Funciones de Dibujo

```c
// Inicialización
void GLCD_Init(void);
void GLCD_Clear(uint16_t color);

// Píxeles y líneas
void GLCD_SetPixel(uint16_t x, uint16_t y, uint16_t color);
uint16_t GLCD_GetPixel(uint16_t x, uint16_t y);
void GLCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

// Formas
void GLCD_DrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void GLCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void GLCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void GLCD_FillCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

// Texto
void GLCD_SetFont(const GLCD_Font_t *font);
void GLCD_PutChar(uint16_t x, uint16_t y, char c, uint16_t fg, uint16_t bg);
void GLCD_PutString(uint16_t x, uint16_t y, const char *str, uint16_t fg, uint16_t bg);
void GLCD_Printf(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, const char *fmt, ...);
```

#### Colores Predefinidos

```c
#define GLCD_COLOR_BLACK   0x0000
#define GLCD_COLOR_WHITE   0xFFFF
#define GLCD_COLOR_RED     0xF800
#define GLCD_COLOR_GREEN   0x07E0
#define GLCD_COLOR_BLUE    0x001F
#define GLCD_COLOR_YELLOW  0xFFE0
#define GLCD_COLOR_CYAN    0x07FF
#define GLCD_COLOR_MAGENTA 0xF81F
```

#### Fuentes Disponibles

- `fuente_8x16` - Fuente pequeña (8x16 píxeles)
- `fuente_12x24` - Fuente mediana (12x24 píxeles)
- `fuente_16x32` - Fuente grande (16x32 píxeles)

#### Ejemplo de Uso

Ver `main_base.c`, `01_GLCD` para ejemplos gráficos.

---

### 🎨 Clases Gráficas (clases_*.h)

**Archivos:** `clases_base.h`, `clases_informatica.h`, `clases_sabem.h`

Definiciones de colores y constantes para diferentes asignaturas.

#### Características

- Paletas de colores predefinidas
- Constantes para posiciones en pantalla
- Macros de utilidad específicas de cada curso

---

## Librerías de Sensores

### 🌡️ LM75B (lm75b_lpc40xx)

**Archivos:** `lm75b_lpc40xx.h`, `lm75b_lpc40xx.c`

Sensor de temperatura digital I2C.

#### Características

- Rango: -55°C a +125°C
- Precisión: ±2°C (típica)
- Resolución: 0.125°C (11 bits)
- Interfaz I2C (dirección 0x48)
- Incluido en la Developer's Kit

#### Funciones Principales

```c
void LM75B_Init(LPC_I2C_TypeDef *i2c);
float LM75B_ReadTemperature(LPC_I2C_TypeDef *i2c);
```

#### Ejemplo de Uso

Ver `main_lm75b.c` para lectura de temperatura.

---

### 💡 LDR (ldr)

**Archivos:** `ldr.h`, `ldr.c`

Conversión de voltaje de LDR a iluminancia.

#### Características

- Conversión de valor ADC a luxes
- Tabla de calibración mediante interpolación
- Soporta múltiples modelos de LDR

#### Funciones Principales

```c
void LDR_Init(void);
float LDR_ReadLux(uint16_t adc_value);
```

#### Ejemplo de Uso

Ver `main_ldr.c` para medición de luz.

---

### 🌡️ NTC (ntc)

**Archivos:** `ntc.h`, `ntc.c`

Conversión de voltaje de termistor NTC a temperatura.

#### Características

- Ecuación de Steinhart-Hart
- Tabla de calibración
- Compensación de divisor de tensión

#### Funciones Principales

```c
void NTC_Init(void);
float NTC_ReadTemperature(uint16_t adc_value);
```

#### Ejemplo de Uso

Ver `main_ntc.c` para medición de temperatura con NTC.

---

## Librerías de Actuadores

### 🚥 LEDs (leds)

**Archivos:** `leds.h`, `leds.c`

Control de los 4 LEDs integrados en la tarjeta.

#### Características

- Control individual de cada LED
- Estados: encendido, apagado, toggle
- Acceso rápido mediante macros

#### Funciones Principales

```c
void LED_Init(void);
void LED_On(uint8_t led);
void LED_Off(uint8_t led);
void LED_Toggle(uint8_t led);
void LED_SetState(uint8_t led, bool_t state);
```

#### Constantes

```c
#define LED1  0  // P1.18
#define LED2  1  // P0.13
#define LED3  2  // P1.13
#define LED4  3  // P2.19
```

---

### 🌈 LED RGB (led_rgb)

**Archivos:** `led_rgb.h`, `led_rgb.c`

Control de LED RGB mediante PWM.

#### Características

- Control de intensidad de cada canal (R, G, B)
- Colores predefinidos
- Mezcla de colores
- Conversión RGB888 a componentes

#### Funciones Principales

```c
void LED_RGB_Init(void);
void LED_RGB_SetColor(uint32_t color);
void LED_RGB_SetRGB(uint8_t r, uint8_t g, uint8_t b);
uint32_t LED_RGB_MakeColor(uint8_t r, uint8_t g, uint8_t b);
```

#### Colores Predefinidos

```c
#define LED_RGB_ROJO     0xFF0000
#define LED_RGB_VERDE    0x00FF00
#define LED_RGB_AZUL     0x0000FF
#define LED_RGB_AMARILLO 0xFFFF00
#define LED_RGB_CYAN     0x00FFFF
#define LED_RGB_MAGENTA  0xFF00FF
#define LED_RGB_BLANCO   0xFFFFFF
#define LED_RGB_NEGRO    0x000000
```

#### Ejemplo de Uso

Ver `main_led_rgb.c` para control de color.

---

### 🎯 Servo (servo_pwm)

**Archivos:** `servo_pwm.h`, `servo_pwm.c`

Control de servomotor de rotación continua mediante PWM.

#### Características

- Control de dirección y velocidad
- Calibración para servo HSR-1425CR
- Pulsos de 1-2 ms (50 Hz)

#### Funciones Principales

```c
void SERVO_Init(void);
void SERVO_SetSpeed(int8_t speed);  // -100 a +100
void SERVO_Stop(void);
```

#### Ejemplo de Uso

Ver `main_servo_pwm.c` para control de servo.

---

### 🎵 Sonido (sonido)

**Archivos:** `sonido.h`, `sonido.c`, `sonido_mario.h`

Generación de tonos y melodías.

#### Características

- Notas musicales predefinidas
- Duración configurable
- Reproducción de melodías
- Ejemplo: melodía de Super Mario Bros

#### Estructuras

```c
typedef struct {
    uint16_t frecuencia;  // Hz o nota predefinida
    uint16_t duracion;    // ms
} Nota_t;

typedef struct {
    const Nota_t *notas;
    uint16_t num_notas;
} Melodia_t;
```

#### Funciones Principales

```c
void SONIDO_Init(void);
void SONIDO_Tono(uint16_t frecuencia, uint16_t duracion);
void SONIDO_Nota(uint8_t nota, uint16_t duracion);
void SONIDO_Melodia(const Melodia_t *melodia);
void SONIDO_Silencio(uint16_t duracion);
```

#### Ejemplo de Uso

Ver `main_melodia.c` para reproducción de música.

---

## Librerías de Juegos

### 🎮 Joystick (joystick)

**Archivos:** `joystick.h`, `joystick.c`

Lectura del joystick de 5 direcciones.

#### Características

- Detección de 5 posiciones + centro
- Lectura por ADC con umbrales
- Debounce por software

#### Funciones Principales

```c
void JOYSTICK_Init(void);
uint8_t JOYSTICK_Read(void);
```

#### Constantes

```c
#define JOYSTICK_CENTRO    0x00
#define JOYSTICK_ARRIBA    0x01
#define JOYSTICK_ABAJO     0x02
#define JOYSTICK_IZQUIERDA 0x04
#define JOYSTICK_DERECHA   0x08
#define JOYSTICK_SIN_PULSAR 0x10
```

---

### 🎮 Tetris (Proyecto Completo)

**Archivos:** `bloque.h/.c`, `cubeta.h/.c`, `piezas.h/.c`, `juego.h/.c`, `marcador.h/.c`, `menu.h/.c`

Implementación completa del juego Tetris.

#### Componentes

**Bloque** - Unidad básica de las piezas

```c
typedef struct {
    uint16_t x, y;       // Posición en pantalla
    uint16_t color;      // Color RGB565
    bool_t ocupado;      // Estado
} Bloque_t;
```

**Pieza** - Tetrominos del juego

```c
typedef enum {
    PIEZA_I, PIEZA_O, PIEZA_T, PIEZA_S,
    PIEZA_Z, PIEZA_J, PIEZA_L
} TipoPieza_t;

typedef struct {
    TipoPieza_t tipo;
    uint8_t rotacion;
    int16_t x, y;
    uint16_t color;
    uint8_t matriz[PIEZA_TAM][PIEZA_TAM];
} Pieza_t;
```

**Cubeta** - Área de juego

```c
typedef struct {
    Bloque_t bloques[CUBETA_FILAS][CUBETA_COLUMNAS];
    uint16_t x, y;       // Posición en pantalla
    uint16_t ancho, alto;
} Cubeta_t;
```

**Juego** - Lógica principal

```c
void JUEGO_Init(void);
void JUEGO_Loop(void);
void JUEGO_MoverPieza(int8_t dx, int8_t dy);
void JUEGO_RotarPieza(void);
bool_t JUEGO_PuedeColocar(Pieza_t *pieza, int16_t x, int16_t y);
void JUEGO_FijarPieza(void);
void JUEGO_EliminarLineasCompletas(void);
```

**Marcador** - Puntuación

```c
void MARCADOR_Init(void);
void MARCADOR_Actualizar(uint16_t lineas);
void MARCADOR_Dibujar(void);
uint32_t MARCADOR_GetPuntuacion(void);
```

**Menú** - Interfaz de usuario

```c
void MENU_Principal(void);
void MENU_Configuracion(void);
void MENU_GameOver(void);
```

#### Ejemplo de Uso

Ver `main_tetris.c` y proyecto `02.1_Tetris`.

---

## Utilidades y Tipos

### 🛠️ Tipos (tipos.h)

**Archivo:** `tipos.h`

Definiciones de tipos y macros de utilidad.

#### Tipos Definidos

```c
// Tipos enteros estándar
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;

// Tipo booleano
typedef uint8_t bool_t;
#define TRUE  1
#define FALSE 0
```

#### Macros de Manipulación de Bits

```c
// Establecer bit
#define _BIT(n)  (1u << (n))

// Campo de bits
#define _CAMPO(f, v)  ((v) << (f))

// Leer bit
#define BIT_READ(reg, bit)  (((reg) >> (bit)) & 1u)

// Establecer/Limpiar bit
#define BIT_SET(reg, bit)    ((reg) |= _BIT(bit))
#define BIT_CLEAR(reg, bit)  ((reg) &= ~_BIT(bit))
```

#### Macros Matemáticas

```c
// Máximo/Mínimo
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

// Valor absoluto
#define ABS(x)  (((x) >= 0) ? (x) : -(x))

// Limitar rango
#define CLAMP(x, min, max)  (MAX(MIN((x), (max)), (min)))

// Cuadrado
#define SQ(x)  ((x) * (x))

// Mapear rango
#define MAP(x, in_min, in_max, out_min, out_max) \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

// Redondeo
#define CEIL(x, n)   ((int32_t)(((x) + ((n) - 1)) / (n)) * (n))
#define FLOOR(x, n)  ((int32_t)((x) / (n)) * (n))
#define ROUND(x, n)  FLOOR((x) + (n) / 2.0, (n))
```

---

### ⚠️ Error (error)

**Archivos:** `error.h`, `error.c`

Sistema de manejo de errores.

#### Características

- Códigos de error predefinidos
- Mensajes de error descriptivos
- Indicación visual de errores

#### Funciones Principales

```c
void ERROR_Handler(uint32_t error_code);
void ERROR_Display(const char *message);
```

---

## Estructura de Proyectos Keil

Cada proyecto Keil (`.uvprojx`) incluye:

- Archivos fuente necesarios
- Configuración del microcontrolador
- Opciones de compilación optimizadas
- Configuración de depuración
- Scripts de enlazado personalizados

### Workspace Principal

El archivo `00_Librerias.uvmpw` contiene todos los proyectos organizados:

1. **Proyectos Base** (01-03)
2. **Periféricos** (04-13)
3. **Proyectos Avanzados** (99.x)

## Generación de Documentación

### Doxygen

El proyecto incluye configuración de Doxygen para generar documentación HTML/PDF.

#### Archivos de Configuración

- `Doxyfile` - Configuración principal
- `DoxygenLayout.xml` - Personalización del layout

#### Generar Documentación

```bash
doxygen Doxyfile
```

La documentación se generará en `docs/html/index.html`.

## Convenciones de Código

### Nomenclatura

- **Funciones:** `MODULO_Funcion()` (PascalCase con prefijo)
- **Variables:** `nombre_variable` (snake_case)
- **Constantes:** `CONSTANTE` (MAYÚSCULAS)
- **Tipos:** `Tipo_t` (PascalCase con sufijo _t)
- **Enumeraciones:** `enum nombre { VALOR1, VALOR2 }`

### Comentarios

```c
/**
 * @brief   Descripción breve de la función.
 *
 * @param   parametro1  Descripción del parámetro.
 * @param   parametro2  Descripción del parámetro.
 * @return  Descripción del valor de retorno.
 *
 * @note    Notas adicionales.
 * @warning Advertencias importantes.
 */
```

## Dependencias entre Librerías

```text
glcd
├── sdram
├── fuente
└── tipos

gpio_lpc40xx
├── iocon_lpc40xx
└── tipos

uart_lpc40xx
├── iocon_lpc40xx
└── tipos

adc_lpc40xx
├── iocon_lpc40xx
└── tipos

spi_lpc40xx
├── iocon_lpc40xx
├── gpio_lpc40xx
└── tipos

i2c_lpc40xx
├── iocon_lpc40xx
└── tipos

lm75b_lpc40xx
├── i2c_lpc40xx
└── tipos

leds
├── gpio_lpc40xx
└── tipos

led_rgb
├── iocon_lpc40xx (PWM)
└── tipos

joystick
├── adc_lpc40xx
└── tipos

tetris (juego completo)
├── glcd
├── joystick
├── timer_lpc40xx
├── bloque
├── cubeta
├── piezas
├── juego
├── marcador
└── menu
```

## Referencias

Para más información sobre el uso de las librerías:

- [Ejemplos de Código](EJEMPLOS.md) - Proyectos de ejemplo
- [Documentación de Hardware](HARDWARE.md) - Especificaciones del hardware
- [Guía de Instalación](INSTALACION.md) - Configuración del entorno

Para la documentación completa de la API, genera la documentación Doxygen o consulta los archivos de cabecera (`.h`) de cada librería.

---

**Última actualización:** 2025
