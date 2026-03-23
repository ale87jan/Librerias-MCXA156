# Project Context

When working with this codebase, prioritize readability over cleverness. Ask clarifying questions before making architectural changes.

## About This Project

Educational C library for NXP MCXA156 microcontroller (ARM Cortex-M33) used at Universidad de Cádiz. Targets Keil µVision IDE with ARM Compiler 6. Focus: teaching embedded systems through well-documented, Spanish-named APIs.

## Key Directories

- `Librerias/` — MCXA156 library projects (Keil µVision, `.uvprojx`)
- `Librerias_LPC/` — deprecated LPC4088 libraries; reference only, do not modify
- `Referencias/` — technical datasheets and reference manuals
- `CMSIS Driver templates/` — CMSIS-compliant driver skeletons; use as the starting point when implementing a new peripheral driver
- `docs_plantilla/` — Markdown documentation templates (hardware, install, library API, examples); use when creating documentation for a new library

## Critical Architecture

### Hardware Abstraction Layers

- **Peripheral Drivers** (`*_mcxa15x.{c,h}`): Direct register manipulation for UART, SPI, I2C, ADC, Timer, GPIO, RTC, etc.
- **High-Level Components**: `driver` followed by component name: `gpio_joystick.{c,h}`, `gpio_leds.{c,h}`
- **Hardware:** FRDM-MCXA156 with LCD-PAR-S035 LCD

**Key Projects:** `Librerias/` contains 20+ example projects (`*.uvprojx` for Keil µVision) demonstrating peripherals (GPIO, UART, ADC, DAC, PWM, SPI, I2C, RTC, Timer) and a complete Tetris game implementation.

**Critical Pattern:** All peripheral libraries follow `modulo_funcion_descriptiva()` snake_case naming with Spanish function names (e.g., `gpio_ajustar_dir()`, `glcd_inicializar()`). This is intentional for educational clarity in Spanish-speaking universities.

## Educational Context

This is a **teaching** repository — clarity beats optimization. When writing or modifying code:

- **Do not** rename or translate Spanish identifiers — they are intentional
- **Do not** merge similar functions — each concept gets its own function
- **Do not** omit Doxygen blocks — explain _why_, not just _what_
- Replace all magic numbers with named constants

## Detailed Guides

- **Git Workflow**: Commit types, branch naming, PR checklist → [.claude/git.md](.claude/git.md)
- **C Style**: Naming, K&R formatting, declarations, spacing → [.claude/estiloC.md](.claude/estiloC.md)
- **Doxygen Documentation**: Templates for files, functions, macros, enums → [.claude/docDoxygen.md](.claude/docDoxygen.md)
- **Assembler Style**: Columnar format, registers, ARM comments → [.claude/estiloEnsamblador.md](.claude/estiloEnsamblador.md)
- **Testing and Validation**: Hardware verification, no unit tests → [.claude/testing.md](.claude/testing.md)
- **Contribution Guidelines** (human-facing, full detail) → [CONTRIBUTING.md](CONTRIBUTING.md)

**Contact:** alejandro.lara@uca.es (project maintainer)
