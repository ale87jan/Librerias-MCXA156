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

## Proyectos Base

### 01 - GLCD

**Proyecto:** `01_GLCD.uvprojx`
**Archivo:** `main_base.c` (configuración inicial)

#### Descripción

Introducción a la pantalla LCD gráfica de 4.3". Muestra cómo inicializar la pantalla y utilizar las funciones básicas de dibujo.

#### Conceptos Aprendidos

- Inicialización de la SDRAM
- Inicialización del controlador LCD
- Limpieza de pantalla
- Dibujo de píxeles
- Dibujo de líneas y formas
- Escritura de texto con diferentes fuentes
- Uso de colores RGB565

#### Funciones Demostradas

```c
GLCD_Init();
GLCD_Clear(GLCD_COLOR_BLACK);
GLCD_DrawLine(x1, y1, x2, y2, color);
GLCD_FillRect(x, y, w, h, color);
GLCD_PutString(x, y, "Hola", fg, bg);
```

#### Hardware Utilizado

- Pantalla LCD TFT 4.3"
- SDRAM externa

---

### 02 - Base

**Proyecto:** `02_Base.uvprojx`
**Archivo:** `main_base.c`

#### Descripción

Proyecto base completo con bucle principal temporizado y lectura del joystick. Sirve como plantilla para proyectos más complejos.

#### Conceptos Aprendidos

- Configuración del sistema de reloj
- Temporizadores periódicos
- Manejo de interrupciones
- Lectura del joystick
- Control de LEDs
- Estructura de bucle principal

#### Funciones Demostradas

```c
SystemCoreClockUpdate();
TIMER_Init(TIMER0, 1);
TIMER_SetMatch(TIMER0, 0, 100000); // 100ms
JOYSTICK_Init();
LED_Init();

// En bucle principal
if (JOYSTICK_Read() == JOYSTICK_ARRIBA) {
    // Acción
}
```

#### Hardware Utilizado

- Timer0
- Joystick (ADC0.0)
- LEDs de usuario

---

### 02.1 - Tetris

**Proyecto:** `02.1_Tetris.uvprojx`
**Archivo:** `main_tetris.c`

#### Descripción

Implementación completa del juego Tetris. Proyecto complejo que integra múltiples librerías.

#### Conceptos Aprendidos

- Arquitectura de juegos
- Estructuras de datos complejas
- Colisiones y física básica
- Interfaz de usuario
- Animaciones
- Puntuación y niveles
- Estado del juego

#### Componentes del Juego

- **Cubeta:** Área de juego 10x20 bloques
- **Piezas:** 7 tetrominos (I, O, T, S, Z, J, L)
- **Rotación:** Sistema de rotación de piezas
- **Colisión:** Detección de colisiones
- **Puntuación:** Sistema de scoring
- **Menú:** Pantalla de inicio y game over

#### Funciones Principales

```c
JUEGO_Init();
JUEGO_Loop();
JUEGO_MoverPieza(dx, dy);
JUEGO_RotarPieza();
JUEGO_EliminarLineasCompletas();
```

#### Hardware Utilizado

- Pantalla LCD completa
- Joystick para control
- LEDs para efectos
- Timer para velocidad del juego

---

### 03 - Base sin Timer

**Proyecto:** `03_Base_sin_timer.uvprojx`
**Archivo:** Similar a `main_base.c`

#### Descripción

Variación del proyecto base que no utiliza temporizadores, solo bucle principal con delays.

#### Conceptos Aprendidos

- Delays por software
- Bucle principal simple
- Polling de entradas

---

## Periféricos

### 04 - ADC

**Proyecto:** `04_ADC.uvprojx`
**Archivo:** `main_adc.c`

#### Descripción

Conversión analógico-digital básica. Lee canales ADC y muestra los valores en pantalla.

#### Conceptos Aprendidos

- Configuración del ADC
- Lectura de canales individuales
- Conversión de valor ADC a voltaje
- Visualización de datos analógicos
- Muestreo continuo

#### Funciones Demostradas

```c
ADC_Init();
ADC_ChannelConfig(ADC_CHANNEL_3, TRUE);
uint16_t valor = ADC_Read(ADC_CHANNEL_3);
float voltaje = ADC_ToVoltage(valor);
```

#### Hardware Utilizado

- ADC0.3 (Potenciómetro)
- ADC0.0 (Joystick)
- Pantalla LCD para visualización

#### Salida Típica

```text
Canal 3: 2048 (1.65V)
Canal 0: 4095 (3.30V)
```

---

### 05 - UART

**Proyecto:** `05_UART.uvprojx`
**Archivo:** `main_uart.c`

#### Descripción

Comunicación serie con PC. Envío y recepción de datos por UART0.

#### Conceptos Aprendidos

- Configuración de UART (baudrate, bits, paridad)
- Transmisión de caracteres y strings
- Recepción de datos
- Echo de caracteres
- Buffering de datos

#### Funciones Demostradas

```c
UART_Init(UART0, 115200);
UART_SendString(UART0, "Hola desde LPC4088\n");
if (!UART_CheckBusy(UART0)) {
    uint8_t dato = UART_ReceiveByte(UART0);
    UART_SendByte(UART0, dato); // Echo
}
```

#### Hardware Utilizado

- UART0 (pines P0.2-TXD, P0.3-RXD)
- Conversor USB-Serie (integrado en la tarjeta)

#### Configuración Terminal

- Baudrate: 115200
- Bits de datos: 8
- Paridad: Ninguna
- Bits de stop: 1
- Control de flujo: Ninguno

---

### 06 - PWM

**Proyecto:** `06_PWM.uvprojx`
**Archivo:** `main_servo_pwm.c`, `main_led_rgb.c`

#### Descripción

Modulación por ancho de pulso para control de servos y LED RGB.

#### Conceptos Aprendidos

- Generación de señales PWM
- Configuración de frecuencia y duty cycle
- Control de servomotores
- Control de intensidad de LEDs
- Mezcla de colores RGB

#### Ejemplo: Servo

```c
SERVO_Init();
SERVO_SetSpeed(50);   // 50% velocidad adelante
delay_ms(2000);
SERVO_SetSpeed(-50);  // 50% velocidad atrás
delay_ms(2000);
SERVO_Stop();
```

#### Ejemplo: LED RGB

```c
LED_RGB_Init();
LED_RGB_SetColor(LED_RGB_ROJO);
delay_ms(1000);
LED_RGB_SetRGB(255, 128, 0);  // Naranja
```

#### Hardware Utilizado

- PWM1 (varios canales)
- Servo HSR-1425CR
- LED RGB de ánodo común

---

### 07 - RTC

**Proyecto:** `07_RTC.uvprojx`
**Archivo:** `main_rtc.c`

#### Descripción

Reloj en tiempo real con fecha, hora y alarma.

#### Conceptos Aprendidos

- Configuración del RTC
- Ajuste de fecha y hora
- Lectura del reloj
- Configuración de alarmas
- Interrupciones del RTC
- Formato de fecha/hora

#### Funciones Demostradas

```c
RTC_Init();
RTC_SetTime(12, 30, 0);     // 12:30:00
RTC_SetDate(2025, 10, 14);  // 14/10/2025

RTC_FechaHora_t now = RTC_GetDateTime();
printf("%02d:%02d:%02d\n", now.hora, now.minuto, now.segundo);

// Configurar alarma
RTC_FechaHora_t alarma = {0, 35, 12, 14, 10, 2025, 0};
RTC_SetAlarm(&alarma, RTC_ALARMA_MASCARA_SEGUNDO);
```

#### Hardware Utilizado

- RTC interno
- Cristal de 32.768 kHz
- Pantalla LCD para visualización

#### Salida Típica

```text
Fecha: 14/10/2025 Martes
Hora:  12:30:45
Alarma: 12:35:00
```

---

### 08 - SPI

**Proyecto:** `08_SPI.uvprojx`
**Archivo:** Código en proyecto

#### Descripción

Comunicación SPI con dispositivos externos.

#### Conceptos Aprendidos

- Configuración SPI (modo, velocidad)
- Transferencia de datos
- Control de Chip Select
- Lectura y escritura simultánea

#### Funciones Demostradas

```c
SPI_Init(SSP0, 1000000);  // 1 MHz
SPI_ConfigMode(SSP0, SPI_CPOL_LOW, SPI_CPHA_FIRST);

GPIO_ClearValue(PORT_CS, PIN_CS);  // CS = 0
uint16_t dato = SPI_Transfer(SSP0, 0xAA);
GPIO_SetValue(PORT_CS, PIN_CS);    // CS = 1
```

#### Hardware Utilizado

- SSP0 (P0.15-SCK, P0.17-MISO, P0.18-MOSI)
- GPIO para Chip Select

---

### 09 - I2C

**Proyecto:** `09_I2C.uvprojx`
**Archivo:** `main_lm75b.c`

#### Descripción

Comunicación I2C con sensor de temperatura LM75B.

#### Conceptos Aprendidos

- Configuración I2C
- Direccionamiento de dispositivos
- Lectura de registros
- Escritura de configuración
- Protocolo Start-Stop

#### Funciones Demostradas

```c
I2C_Init(I2C0, 100000);  // 100 kHz
LM75B_Init(I2C0);

float temperatura = LM75B_ReadTemperature(I2C0);
printf("Temperatura: %.2f C\n", temperatura);
```

#### Hardware Utilizado

- I2C0 (P0.27-SDA, P0.28-SCL)
- Sensor LM75B (dirección 0x48)

#### Salida Típica

```text
Sensor LM75B
Temperatura: 23.50°C
```

---

### 11 - DAC

**Proyecto:** `11_DAC.uvprojx`
**Archivo:** Pendiente

#### Descripción

Conversión digital-analógico. Generación de señales analógicas.

#### Conceptos

- Configuración del DAC
- Generación de formas de onda
- Señales de audio

---

### 12 - Teclado

**Proyecto:** `12_Teclado.uvprojx`
**Archivo:** `main_teclado.c`

#### Descripción

Lectura de teclado matricial 4x4.

#### Conceptos Aprendidos

- Escaneo matricial
- Debounce de teclas
- Detección de pulsaciones
- Mapeo de teclas

#### Hardware Utilizado

- GPIOs para filas y columnas
- Teclado matricial 4x4 externo

---

### 13 - Sonido

**Proyecto:** `13_Sonido.uvprojx`
**Archivo:** `main_melodia.c`

#### Descripción

Generación de tonos musicales y reproducción de melodías.

#### Conceptos Aprendidos

- Generación de frecuencias
- Notas musicales
- Duraciones
- Reproducción de melodías

#### Funciones Demostradas

```c
SONIDO_Init();
SONIDO_Nota(NOTA_DO4, 500);
SONIDO_Nota(NOTA_RE4, 500);
SONIDO_Nota(NOTA_MI4, 500);
SONIDO_Melodia(&melodia_mario);
```

#### Hardware Utilizado

- PWM para generación de tono
- Buzzer o altavoz

---

## Proyectos Avanzados

### 99.1 - Stepper

**Proyecto:** `99.1_Stepper.uvprojx`

#### Descripción

Control de motor paso a paso.

#### Conceptos

- Secuencias de paso completo/medio paso
- Control de velocidad
- Control de dirección
- Posicionamiento

#### Hardware Utilizado

- Motor paso a paso bipolar
- Driver externo (L298N, ULN2003, etc.)

---

### 99.2 - LCD I2C

**Proyecto:** `99.2_LCD I2C.uvprojx`

#### Descripción

Control de display LCD de caracteres 16x2 o 20x4 con interfaz I2C (PCF8574).

#### Conceptos

- Protocolo I2C
- Control de LCD de caracteres
- Escritura de texto
- Caracteres personalizados

#### Hardware Utilizado

- LCD 16x2/20x4
- Módulo I2C PCF8574

---

### 99.3 - DHT

**Proyecto:** `99.3_DHT.uvprojx`

#### Descripción

Lectura de sensores de temperatura y humedad DHT11/DHT22.

#### Conceptos

- Protocolo One-Wire
- Timing crítico
- Lectura de humedad relativa
- Lectura de temperatura

#### Hardware Utilizado

- Sensor DHT11 o DHT22
- Pull-up resistor 4.7kΩ

---

### 99.4 - A4988

**Proyecto:** `99.4_A4988.uvprojx`

#### Descripción

Control de motor paso a paso con driver A4988.

#### Conceptos

- Generación de pulsos de paso
- Control de dirección
- Microstepping
- Control de habilitación

#### Hardware Utilizado

- Driver A4988
- Motor paso a paso NEMA17
- Fuente de alimentación externa

---

### 99.5 - Táctil

**Proyecto:** `99.5_Tactil.uvprojx`

#### Descripción

Lectura de la pantalla táctil resistiva con controlador TSC2046.

#### Conceptos

- Lectura táctil por SPI
- Calibración de pantalla
- Detección de toques
- Conversión de coordenadas

#### Hardware Utilizado

- Panel táctil integrado en LCD
- Controlador TSC2046 (SPI)

---

### 99.6 - Ultrasonidos

**Proyecto:** `99.6_Ultrasonidos.uvprojx`

#### Descripción

Medición de distancia con sensor ultrasónico HC-SR04.

#### Conceptos

- Generación de pulso trigger
- Medición de eco
- Cálculo de distancia
- Timer capture

#### Hardware Utilizado

- Sensor HC-SR04
- GPIOs para trigger y echo

---

### 99.7 - RFID

**Proyecto:** `99.7_RFID.uvprojx`

#### Descripción

Lectura de tarjetas RFID con módulo RC522.

#### Conceptos

- Protocolo SPI avanzado
- Anticoli sión RFID
- Lectura de UID
- Autenticación de sectores
- Lectura/escritura de bloques

#### Hardware Utilizado

- Módulo RFID RC522 (SPI)
- Tarjetas/llaveros RFID MIFARE

---

## Proyectos Sugeridos

Basándote en los ejemplos, puedes crear:

### Nivel Básico

- ✅ Termómetro digital con LM75B
- ✅ Control de LED RGB con joystick
- ✅ Reloj digital con RTC
- ✅ Voltímetro con ADC

### Nivel Intermedio

- 🎮 Juego de Simon Says
- 📊 Graficador de datos del ADC
- 🌡️ Estación meteorológica (DHT + LCD)
- 🎵 Piano con teclado y buzzer

### Nivel Avanzado

- 🤖 Control de robot con motores paso a paso
- 🔐 Sistema de acceso con RFID
- 📱 Interfaz táctil completa
- 🎮 Juego tipo Snake o Pong
