# Librerías MCXA156

Directorio de proyectos Keil µVision con las librerías docentes para el
microcontrolador NXP MCXA156 (ARM Cortex-M33).

## Estructura prevista

Cada librería se organizará como un proyecto Keil independiente:

```text
Librerias/
├── base/               Proyecto base (GPIO, PORT, reloj)
├── uart/               Comunicación serie LPUART
├── adc/                Conversión analógico-digital LPADC
├── dac/                Conversión digital-analógico LPDAC
├── pwm/                Generación PWM (FlexPWM / CTimer)
├── spi/                Comunicación SPI (LPSPI)
├── i2c/                Comunicación I2C (LPI2C)
├── rtc/                Reloj de tiempo real
├── timer/              Temporizadores CTimer
├── glcd/               Librería gráfica para LCD-PAR-S035
└── tetris/             Proyecto completo del juego Tetris
```

## Convenciones

- Archivos de driver: `<periferico>_mcxa15x.{c,h}`
- Funciones: `modulo_funcion_descriptiva()` (snake_case, español)
- Documentación: Doxygen en cada función pública
- IDE: Keil µVision 5, ARM Compiler 6

Consulta [docs_plantilla/LIBRERIAS.md](../docs_plantilla/LIBRERIAS.md) para
la documentación completa de la API.
