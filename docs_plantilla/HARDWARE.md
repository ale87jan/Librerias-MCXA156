<!-- LICENSE INFORMATION
Copyright (C) 2025 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Hardware - LPC4088 Developer's Kit

## 📦 Contenido

- [Especificaciones del LPC4088](#especificaciones-del-lpc4088)
- [Embedded Artists LPC4088 Developer's Kit](#embedded-artists-lpc4088-developers-kit)
- [Periféricos Integrados](#periféricos-integrados)
- [Pinout y Conectores](#pinout-y-conectores)
- [Esquemas y Diagramas](#esquemas-y-diagramas)

## Especificaciones del LPC4088

### Microcontrolador NXP LPC4088FBD208

El **LPC4088** es un microcontrolador ARM Cortex-M4 de alto rendimiento con las siguientes características:

#### Procesador y Memoria

- **Core:** ARM Cortex-M4 con FPU (Floating Point Unit)
- **Frecuencia:** Hasta 120 MHz
- **Flash:** 512 KB
- **SRAM:** 96 KB (64 KB local + 32 KB AHB)
- **ROM:** 16 KB (bootloader y utilidades)
- **EMC:** Controlador de memoria externa (para SDRAM)

#### Características del Procesador

- Arquitectura ARMv7E-M
- Unidad de punto flotante de precisión simple (FPU)
- Memory Protection Unit (MPU)
- Nested Vectored Interrupt Controller (NVIC)
- Pipeline de 3 etapas
- Instrucciones DSP
- Wake-up Interrupt Controller (WIC)

#### Periféricos de Comunicación

- **UART:** 4 puertos (UART0-UART3)
- **SPI/SSP:** 3 interfaces (SSP0, SSP1, SSP2)
- **I2C:** 3 interfaces (I2C0, I2C1, I2C2)
- **I2S:** 2 interfaces (audio)
- **CAN:** 2 controladores CAN 2.0B
- **Ethernet:** 10/100 MAC con MII/RMII
- **USB:** Host/Device/OTG de alta velocidad

#### Periféricos Analógicos

- **ADC:** 12-bit, 8 canales, hasta 400 kSPS
- **DAC:** 10-bit, hasta 400 kHz
- **Comparador analógico**

#### Temporizadores y PWM

- **Timers:** 4 timers de propósito general de 32-bit
- **PWM:** Motor Control PWM con 6 salidas
- **RTC:** Real-Time Clock con alarma
- **Watchdog Timer**
- **Repetitive Interrupt Timer (RIT)**
- **System Tick Timer**

#### GPIO y Control

- Hasta 164 pines GPIO (5V tolerantes)
- Pin Connect Block para multiplexado de funciones
- External Memory Controller (EMC)
- LCD Controller (hasta 1024x768 con TFT)
- Quadrature Encoder Interface (QEI)

#### Consumo Energético

- Voltaje de operación: 2.4V - 3.6V (I/O: 1.8V - 3.6V)
- Modos de bajo consumo: Sleep, Deep-sleep, Power-down, Deep power-down
- Consumo activo típico: ~0.45 mA/MHz

## Embedded Artists LPC4088 Developer's Kit

La **Embedded Artists LPC4088 Developer's Kit** es una plataforma de desarrollo completa que incluye:

### Componentes Principales

#### Tarjeta Base (OEM Board)

- Microcontrolador LPC4088FBD208 en encapsulado LQFP208
- Cristal de 12 MHz
- Oscilador RTC de 32.768 kHz
- Reguladores de voltaje 3.3V
- Conector USB Device
- Conector USB Host
- Puerto Ethernet 10/100
- Ranura microSD
- Conector JTAG/SWD de 20 pines
- LEDs de usuario (4)
- Pulsadores de usuario (2)
- Potenciómetro analógico
- Sensor de temperatura LM75B (I2C)
- Headers de expansión

#### Pantalla LCD TFT

- Tamaño: 4.3 pulgadas
- Resolución: 480x272 píxeles
- Tecnología: TFT de 16 bits
- Panel táctil resistivo de 4 hilos
- Controlador táctil: TSC2046 (SPI)
- Retroiluminación LED ajustable por PWM
- Interfaz paralela RGB
- Memoria SDRAM de 16 MB (para frame buffer)

#### Interfaces de Expansión

- 2 conectores Arduino-compatible (32 pines c/u)
- Acceso a la mayoría de señales del LPC4088
- Alimentación 3.3V y 5V disponibles

#### Alimentación

- USB (5V)
- Jack DC 7-12V
- Reguladores internos 3.3V y 1.8V

## Periféricos Integrados

### En la Tarjeta Base

| Periférico | Modelo/Especificación | Interfaz | Descripción |
|------------|----------------------|----------|-------------|
| Sensor Temperatura | LM75B | I2C0 | Rango: -55°C a +125°C, precisión ±2°C |
| LED RGB | Común ánodo | PWM | Control de color mediante PWM |
| LEDs Usuario | 4 LEDs rojos | GPIO | P1.18, P0.13, P1.13, P2.19 |
| Pulsadores | 2 botones | GPIO | SW2 (ISP), SW3 (RESET) |
| Potenciómetro | 10kΩ | ADC0.3 | Entrada analógica de prueba |
| Joystick | 5 direcciones | ADC0.0 | Centro, Arriba, Abajo, Izq, Der |
| Ethernet PHY | DP83848C | EMAC | 10/100 Mbps |
| Memoria SDRAM | IS42S16400J | EMC | 16 MB para LCD |
| Memoria Flash SPI | - | SSP1 | Opcional en algunos modelos |

### Panel Táctil

| Componente | Modelo | Interfaz | Pin Señal |
|------------|--------|----------|-----------|
| Controlador Táctil | TSC2046 | SSP0 (SPI) | P0.15 (SCK), P0.17 (MISO), P0.18 (MOSI) |
| Chip Select | - | GPIO | P0.6 |
| Pen IRQ | - | GPIO | P2.10 |

### Conectores de Expansión

Los conectores de expansión permiten conectar:

- Sensores de temperatura/humedad (DHT11, DHT22)
- Displays LCD I2C
- Módulos RFID (RC522)
- Sensores ultrasónicos (HC-SR04)
- Motores paso a paso (con drivers A4988)
- Servomotores
- Teclados matriciales
- Y muchos más...

## Pinout y Conectores

### Conectores Arduino

La tarjeta incluye conectores compatibles con Arduino que dan acceso a:

#### Conector J1 (Señales Digitales)

| Pin | Señal LPC4088 | Función | Notas |
|-----|---------------|---------|-------|
| 0 | P0.3 | UART0_RXD | RX Serie |
| 1 | P0.2 | UART0_TXD | TX Serie |
| 2 | P2.12 | GPIO | Interrupción externa |
| 3 | P0.10 | PWM1.1 | PWM |
| 4 | P2.11 | GPIO | Digital |
| 5 | P1.23 | PWM1.4 | PWM |
| 6 | P1.24 | PWM1.5 | PWM |
| 7 | P1.25 | GPIO | Digital |

#### Conector J2 (Señales Digitales)

| Pin | Señal LPC4088 | Función | Notas |
|-----|---------------|---------|-------|
| 8 | P1.26 | PWM1.6 | PWM |
| 9 | P1.20 | PWM1.2 | PWM |
| 10 | P0.15 | SSP0_SCK | SPI SCK |
| 11 | P0.18 | SSP0_MOSI | SPI MOSI |
| 12 | P0.17 | SSP0_MISO | SPI MISO |
| 13 | P1.21 | PWM1.3 | PWM |
| GND | GND | Tierra | - |
| AREF | - | No conectado | - |
| SDA | P0.0 | I2C1_SDA | I2C Data |
| SCL | P0.1 | I2C1_SCL | I2C Clock |

#### Conector J3 (Señales Analógicas)

| Pin | Señal LPC4088 | Función | Notas |
|-----|---------------|---------|-------|
| A0 | P0.23 | ADC0.0 | Joystick |
| A1 | P0.24 | ADC0.1 | Analógico |
| A2 | P0.25 | ADC0.2 | Analógico |
| A3 | P0.26 | ADC0.3 | Potenciómetro |
| A4 | P1.30 | ADC0.4 | Analógico |
| A5 | P1.31 | ADC0.5 | Analógico |

### LEDs de Usuario

| LED | Pin | Ubicación | Color |
|-----|-----|-----------|-------|
| LED1 | P1.18 | Tarjeta base | Rojo |
| LED2 | P0.13 | Tarjeta base | Rojo |
| LED3 | P1.13 | Tarjeta base | Rojo |
| LED4 | P2.19 | Tarjeta base | Rojo |

### Joystick

El joystick de 5 direcciones está conectado a un divisor resistivo en el canal ADC0.0:

| Posición | Voltaje aproximado | Rango ADC (12-bit) |
|----------|-------------------|-------------------|
| Centro | 0.00V | 0 |
| Arriba | 0.66V | ~820 |
| Derecha | 1.32V | ~1640 |
| Abajo | 1.98V | ~2460 |
| Izquierda | 2.64V | ~3280 |
| Sin pulsar | 3.30V | ~4095 |

## Esquemas y Diagramas

### Recursos Disponibles

En la carpeta `Documentacion LPC4088/` encontrarás:

**Documentación ARM:**

- ARM Cortex-M4 Technical Reference Manual
- ARM v7-M Architecture Reference Manual
- Guías de optimización de código

**Documentación NXP:**

- LPC408x/407x User Manual (UM10562)
- LPC408x/407x Datasheet
- Errata del chip
- Application Notes

**Documentación Embedded Artists:**

- User's Guide de la Developer's Kit
- Esquemáticos de la OEM Board
- Esquemáticos del módulo LCD
- Pinout detallado

**Archivos Útiles:**

- `LPC4088 OEM Board - Pines Conectores.pdf` - Pinout de conectores
- `LPC4088 OEM Board - Pines Prácticas.pdf` - Pines usados en prácticas
- `Tabla Códigos ASCII completa.pdf` - Referencia ASCII

### Diagrama de Bloques Simplificado

```text
                    ┌─────────────────────────────────────┐
                    │        LPC4088 (Cortex-M4)          │
                    │                                     │
    ┌───────────────┤  Core @ 120MHz + FPU               │
    │               │  Flash: 512KB  |  SRAM: 96KB       │
    │               └────────┬────────────────────────────┘
    │                        │
    ├─ USB Device/Host ──────┤
    ├─ Ethernet 10/100 ──────┤
    ├─ UART x4 ──────────────┤──── Conectores Arduino
    ├─ SPI x3 ───────────────┤
    ├─ I2C x3 ───────────────┤──── Sensor LM75B
    ├─ ADC 12-bit x8 ────────┤──── Potenciómetro/Joystick
    ├─ DAC 10-bit ───────────┤
    ├─ PWM x6 ───────────────┤──── LED RGB
    ├─ Timer x4 ─────────────┤
    ├─ GPIO x164 ────────────┤──── LEDs, Botones
    ├─ RTC ──────────────────┤
    └─ LCD Controller ───────┴──── LCD 4.3" 480x272
                                   Panel Táctil (TSC2046)
                                   SDRAM 16MB (Frame Buffer)
```

## Características Eléctricas

### Alimentación interna

- **Voltaje de entrada:** 7-12V DC o 5V USB
- **Consumo típico (activo):** 200-300 mA (con LCD)
- **Consumo en sleep:** < 50 mA
- **Voltajes internos:** 3.3V y 1.8V (regulados)

### GPIO

- **Voltaje lógico:** 3.3V (5V tolerante en algunos pines)
- **Corriente máxima por pin:** 4 mA (típico), 20 mA (máximo)
- **Corriente total GPIO:** 100 mA (máximo)

### ADC

- **Resolución:** 12 bits
- **Voltaje de referencia:** 3.3V
- **Rango de entrada:** 0 - 3.3V
- **Velocidad de muestreo:** Hasta 400 kSPS

### DAC

- **Resolución:** 10 bits
- **Voltaje de salida:** 0 - 3.3V (referencia VREFP)
- **Velocidad de actualización:** Hasta 400 kHz

## Referencias

### Enlaces Oficiales

- [NXP LPC4088 Product Page](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc4000-arm-cortex-m4/scalable-entry-level-32-bit-microcontroller-mcu-based-on-arm-cortex-m4-core:LPC408X_7X)
- [Embedded Artists Developer's Kit](https://www.embeddedartists.com/products/lpc4088-developer-kit/)
- [ARM Cortex-M4 Documentation](https://developer.arm.com/ip-products/processors/cortex-m/cortex-m4)

### Documentos de Referencia

Para acceder a la documentación completa, consulta la carpeta:

```text
Documentacion LPC4088/
├── ARM/                    # Documentación del core ARM Cortex-M4
├── NXP/                    # Manuales de usuario y datasheets
├── Embedded Artists/       # Guías de la Developer's Kit
└── Libros Referencia/      # Material adicional de referencia
```

---

**Nota:** Para información sobre cómo usar estos periféricos desde el código, consulta [LIBRERIAS.md](LIBRERIAS.md).
