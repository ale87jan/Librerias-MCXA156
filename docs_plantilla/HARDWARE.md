<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Hardware — FRDM-MCXA156

## Contenido

- [Placa de Desarrollo](#placa-de-desarrollo)
- [Microcontrolador MCXA156](#microcontrolador-mcxa156)
- [Conectores de Expansión](#conectores-de-expansión)
- [LEDs y Botones](#leds-y-botones)
- [Pantalla LCD](#pantalla-lcd)
- [Depuración y Programación](#depuración-y-programación)
- [Alimentación](#alimentación)
- [Referencias](#referencias)

---

## Placa de Desarrollo

| Característica | Valor |
| --- | --- |
| **Nombre** | FRDM-MCXA156 |
| **Fabricante** | NXP Semiconductors |
| **Microcontrolador** | MCXA156VLL (LQFP-100) |
| **Depurador integrado** | MCU-Link (CMSIS-DAP / J-Link) |
| **Conectores** | Arduino R3, mikroBUS, FRDM headers, Pmod |
| **USB** | 1× USB FS (MCU), 1× USB MCU-Link (debug) |
| **Alimentación** | 5V USB o fuente externa |

---

## Microcontrolador MCXA156

### Especificaciones Principales

| Característica | Valor |
| --- | --- |
| **Núcleo** | ARM Cortex-M33 |
| **Frecuencia máxima** | 96 MHz |
| **Flash** | 1 MB |
| **SRAM** | 128 KB |
| **FPU** | Single-precision (SFPU) |
| **DSP** | Sí (extensiones DSP del Cortex-M33) |
| **TrustZone** | Sí (ARM TrustZone-M) |
| **Encapsulado** | LQFP-100 |
| **Tensión de operación** | 1.71V – 3.6V |

### Periféricos

| Periférico | Cantidad | Notas |
| --- | --- | --- |
| **GPIO** | 5 puertos (P0-P4) | Hasta 80 pines GPIO |
| **LPUART** | 5 (LPUART0-4) | Low-power UART |
| **LPSPI** | 2 (LPSPI0-1) | Low-power SPI |
| **LPI2C** | 4 (LPI2C0-3) | Low-power I2C |
| **I3C** | 1 | MIPI I3C |
| **LPADC** | 1 (16-bit) | Low-power ADC, múltiples canales |
| **LPDAC** | 1 (12-bit) | Low-power DAC |
| **LPCMP** | 2 | Low-power comparadores analógicos |
| **CTimer** | 5 (CT0-4) | Temporizadores de 32 bits |
| **FlexPWM** | 2 (PWM0-1) | Generación avanzada de PWM |
| **UTICK** | 1 | Micro-tick timer |
| **RTC** | 1 | Reloj de tiempo real |
| **FlexIO** | 1 (32 señales) | E/S flexible programable |
| **USB** | 1 | USB 2.0 FS (Device/Host) |
| **CRC** | 1 | Motor de cálculo CRC |
| **DMA** | 1 (eDMA) | 16 canales |
| **WDT** | 1 | Watchdog timer |

<!-- TODO: Verificar cantidades exactas con el Reference Manual -->

---

## Conectores de Expansión

### Arduino R3 (J1, J2, J3, J4)

La placa dispone de conectores compatibles con el estándar Arduino R3:

| Conector | Pines | Función principal |
| --- | --- | --- |
| **J1** | Digitales | D0-D7 equivalente |
| **J2** | Analógicos/Digitales | A0-A5 equivalente, alimentación |
| **J3** | Digitales | D8-D13 equivalente (SPI) |
| **J4** | Digitales | I2C, alimentación |

<!-- TODO: Completar mapeo Arduino → pines MCXA156 con datos del User Manual -->

### mikroBUS (J5, J6)

Conector mikroBUS estándar para módulos Click de MikroElektronika:

| Pin | Señal | Pin MCXA156 |
| --- | --- | --- |
| AN | Analógica | P3_30 (J6[1]) |
| RST | Reset | P3_29 (J6[2]) |
| CS | SPI Chip Select | P1_3 (J6[3]) |
| SCK | SPI Clock | P1_1 (J6[4]) |
| MISO | SPI Data In | P1_2 (J6[5]) |
| MOSI | SPI Data Out | P1_0 (J6[6]) |
| PWM | PWM | P3_18 (J5[1]) |
| INT | Interrupción | P3_19 (J5[2]) |
| RX | UART Recepción | P3_20 (J5[3]) |
| TX | UART Transmisión | P3_21 (J5[4]) |
| SCL | I2C Clock | P3_27 (J5[5]) |
| SDA | I2C Data | P3_28 (J5[6]) |

### Pmod (J7)

| Pin | Señal | Pin MCXA156 |
| --- | --- | --- |
| 1 | CS / GPIO | P1_3 |
| 2 | SDO / GPIO | P3_19 |
| 3 | SDI / GPIO | P1_0 |
| 4 | SCL / GPIO | P3_20 |
| 5 | SCK / GPIO | P1_2 |
| 6 | SCL_I2C | P3_27 |
| 7 | SCK_SPI | P1_1 |
| 8 | SDA_I2C | P3_28 |

<!-- TODO: Verificar pinout exacto del Pmod con el esquemático -->

### Conector LCD (J8, J9)

Conector dedicado para pantalla LCD-PAR-S035 mediante bus paralelo FlexIO:

| Señal | Pin MCXA156 | Conector |
| --- | --- | --- |
| D0-D7 | P0_16-P0_23 | J8[13-20] |
| D8-D9 | P2_0-P2_1 | J8[21-22] / J9[15-16] |
| D10-D15 | P4_2-P4_7 | J8[23-28] / J9[9-14] |
| RS | P2_17 | J8[8] |
| CS | P2_19 | J8[9] |
| WR | P2_23 | J8[10] |
| RD | P2_20 | J8[11] |
| TE | P2_21 | J8[12] |
| INT | P2_15 | J8[5] |
| RST | P3_0 | J8[7] |
| GPIO | P3_22 | J8[6] |

---

## LEDs y Botones

### LEDs

| LED | Color | Pin MCXA156 | Identificador |
| --- | --- | --- | --- |
| LED RGB (R) | Rojo | P3_12 | `LED_RED` |
| LED RGB (G) | Verde | P3_13 | `LED_GREEN` |
| LED RGB (B) | Azul | P3_0 | `LED_BLUE` |

> **Nota:** El LED azul comparte pin con la señal LCD_RST (P3_0).
> Cuando se usa la LCD, el LED azul no está disponible.

### Botones

| Botón | Función | Pin MCXA156 | Identificador |
| --- | --- | --- | --- |
| SW1 | Reset | P1_29 | `RESET` |
| SW2 | Usuario | P1_7 | `SW2` |
| SW3 | ISP / Usuario | P0_6 | `SW3` / `ISP` |

---

## Pantalla LCD

| Característica | Valor |
| --- | --- |
| **Modelo** | LCD-PAR-S035 |
| **Tamaño** | 3.5 pulgadas |
| **Resolución** | 480 × 320 píxeles |
| **Profundidad de color** | 16 bits (RGB565) |
| **Interfaz** | Paralelo 16-bit (FlexIO) |
| **Controlador** | ST7796S |
| **Retroiluminación** | LED, controlable |

<!-- TODO: Añadir esquema de conexión LCD ↔ FRDM-MCXA156 -->

---

## Depuración y Programación

### MCU-Link (Depurador Integrado)

| Característica | Valor |
| --- | --- |
| **Interfaz** | SWD (Serial Wire Debug) |
| **SWDIO** | P0_0 |
| **SWCLK** | P0_1 |
| **SWO** | P0_2 |
| **Firmware** | CMSIS-DAP (por defecto) o J-Link |
| **UART virtual** | Sí, a través de USB MCU-Link |

### UART de Depuración

| Señal | Pin MCXA156 | Función |
| --- | --- | --- |
| RX | P0_2 | `DEBUG_UART_RX` (LPUART0) |
| TX | P0_3 | `DEBUG_UART_TX` (LPUART0) |

Configuración recomendada: **115200 baud, 8N1**.

---

## Alimentación

| Fuente | Tensión | Notas |
| --- | --- | --- |
| USB MCU-Link | 5V | Depuración + alimentación |
| USB FS (MCU) | 5V | Solo alimentación / USB device |
| VDD MCU | 3.3V | Regulada en placa (JP2) |
| VDDA | 3.3V | Alimentación analógica |
| VDD USB | 3.3V | Alimentación USB PHY |

---

## Referencias

- **User Manual:** *FRDM MCX A156 User Manual* (UM12121) — `Referencias/`
- **Reference Manual:** *MCX A15x, A14x Reference Manual* — `Referencias/`
- **Quick Start Guide:** *FRDM MCX A156 Quick Start Guide* — `Referencias/`
- **Esquemáticos:** `Referencias/Design files/`
- **Pinout:** `Referencias/MCX A14x A15x Pinout.xlsx`
- **Configuración de pines base:** `MCXA156-Base.mex` (raíz del proyecto)

---

**Última actualización:** 2026
