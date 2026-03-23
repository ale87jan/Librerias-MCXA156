<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Librerias-MCXA156

> **Trabajo en curso** — Migración de las librerías docentes del LPC4088 al
> MCXA156 (ARM Cortex-M33).

Librerías docentes en C para el microcontrolador **NXP MCXA156** (ARM
Cortex-M33) sobre la placa de desarrollo **FRDM-MCXA156**, desarrolladas para
la asignatura de **Sistemas Empotrados** de la Universidad de Cádiz.

El objetivo del proyecto es proporcionar librerías de periféricos bien
documentadas, con APIs en español, que permitan a los estudiantes aprender
programación de sistemas embebidos de forma clara y progresiva.

## Características

- APIs en español con convención `modulo_funcion_descriptiva()` (snake_case)
- Documentación Doxygen en cada función pública
- Drivers de periféricos: GPIO, UART, SPI, I2C, ADC, DAC, PWM, Timer, RTC
- Componentes de alto nivel: LEDs, joystick, pantalla LCD (LCD-PAR-S035)
- Plantillas CMSIS para nuevos drivers
- Ejemplos progresivos de uso

## Requisitos

- **IDE:** Keil µVision 5 con ARM Compiler 6
- **Hardware:** placa FRDM-MCXA156 con pantalla LCD-PAR-S035
- **SDK:** NXP MCUXpresso SDK para MCXA156 (incluido en `SDK/`)

## Organización del Repositorio

```text
Librerias-MCXA156/
├── CMSIS_Driver_templates/   Plantillas de drivers CMSIS (GPIO, SPI, I2C, ...)
├── Expansion Board/          Configuraciones XML de placas de expansión
├── Librerias_LPC/            Librerías LPC4088 originales (solo referencia)
├── Referencias/              Datasheets, manuales y esquemáticos
│   ├── Application Notes/    Notas de aplicación de NXP
│   └── Design files/         Archivos de diseño de la placa
├── SDK/                      MCUXpresso SDK para MCXA156
│   ├── CMSIS/                Cabeceras y DSP library de CMSIS
│   ├── boards/               BSP de la FRDM-MCXA156
│   ├── components/           Componentes de software del SDK
│   ├── devices/              Ficheros de dispositivo y startup
│   └── middleware/           Middleware (FreeMASTER, etc.)
├── docs_plantilla/           Plantillas de documentación Markdown
├── MCXA156-Base.mex          Configuración base de MCUXpresso Config Tools
├── CONTRIBUTING.md           Guía rápida de contribución
├── AUTHORS.md                Autores del proyecto
└── LICENSE.md                Licencia GPL v3.0
```

## Cómo Empezar

1. Clona el repositorio:

   ```bash
   git clone https://github.com/ale87jan/Librerias-MCXA156.git
   ```

2. Abre un proyecto `.uvprojx` en Keil µVision 5
   (los proyectos de ejemplo se irán añadiendo a medida que avance la migración).
3. Conecta la placa FRDM-MCXA156 por USB.
4. Compila y descarga el programa a la placa.

## Contribuir

Consulta la [guía rápida de contribución](CONTRIBUTING.md) para el flujo de
trabajo y la [guía detallada](docs_plantilla/CONTRIBUCION.md) para plantillas y
preguntas frecuentes.

## Licencia

- **Código fuente:** [GNU General Public License v3.0](LICENSE.md) o posterior
- **Documentación:** [GNU Free Documentation License v1.3 o posterior](docs_plantilla/LICENSE.md)

## Contacto

Alejandro Lara Doña — [alejandro.lara@uca.es](mailto:alejandro.lara@uca.es)

Universidad de Cádiz — Dpto. de Automática, Electrónica, Arquitectura y Redes
de Computadores (Área de Ingeniería de Sistemas y Automática)
