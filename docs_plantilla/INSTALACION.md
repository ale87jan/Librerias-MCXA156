<!-- LICENSE INFORMATION
Copyright (C) 2025 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Guía de Instalación y Configuración

## 📋 Contenido

- [Requisitos del Sistema](#requisitos-del-sistema)
- [Instalación del Software](#instalación-del-software)
- [Configuración del Hardware](#configuración-del-hardware)
- [Configuración de Keil µVision](#configuración-de-keil-µvision)
- [Primer Proyecto](#primer-proyecto)
- [Solución de Problemas](#solución-de-problemas)

## Requisitos del Sistema

### Hardware Requerido

- **Embedded Artists LPC4088 Developer's Kit**
  - Tarjeta base OEM Board
  - Pantalla LCD TFT 4.3" con táctil
  - Cable USB tipo A a Mini-B (para programación)

- **PC con Windows**
  - Windows 10 o 11 (64-bit recomendado)
  - Procesador: Intel Core i5 o superior
  - RAM: 8 GB mínimo, 16 GB recomendado
  - Espacio en disco: 10 GB libres
  - Puerto USB 2.0 o superior

#### Opcional

- Cable USB adicional (para comunicación serie)
- Fuente de alimentación externa 7-12V DC
- Protoboard y cables para conexiones externas
- Sensores y actuadores según el proyecto

### Software Requerido

1. **Keil µVision IDE**
   - Versión 5.38 o superior
   - Licencia: Evaluación (32 KB límite) o comercial
   - Incluye ARM Compiler 6

2. **Pack de Soporte del Dispositivo**
   - NXP LPC4000 Device Family Pack
   - Se instala desde Pack Installer

3. **Drivers CMSIS-DAP/J-Link**
   - Para depuración y programación
   - Incluidos con Keil o descarga separada

#### Opcional pero Recomendado

1. **Git para Windows**
   - Para clonar el repositorio
   - Control de versiones

2. **Terminal Serie**
   - PuTTY, Tera Term, o similar
   - Para comunicación UART

3. **Doxygen**
   - Generación de documentación
   - GraphViz para diagramas

## Instalación del Software

### Paso 1: Instalar Keil µVision

#### 1.1 Descargar

1. Visita [www.keil.com/download](https://www.keil.com/download/product/)
2. Selecciona **MDK-ARM** (Microcontroller Development Kit)
3. Completa el formulario de registro
4. Descarga el instalador (aprox. 1 GB)

#### 1.2 Instalar

```text
1. Ejecuta el instalador MDK538.EXE (o versión actual)
2. Acepta el acuerdo de licencia
3. Selecciona la ruta de instalación:
   - Por defecto: C:\Keil_v5\
   - Recomendado: mantener la ruta por defecto
4. Desactiva "Install ULINK Drivers" si no tienes ULINK
5. Completa la instalación (10-15 minutos)
```

#### 1.3 Verificar Instalación

```text
1. Abre Keil µVision
2. Debería aparecer la pantalla de inicio
3. Ve a Help → About µVision
4. Verifica la versión
```

### Paso 2: Instalar Device Family Pack

#### 2.1 Abrir Pack Installer

```text
1. En Keil µVision: Project → Manage → Pack Installer
   O directamente desde el menú de Windows
2. Espera a que cargue la lista de packs
```

#### 2.2 Instalar LPC4000 Pack

```text
1. En el panel izquierdo: Devices → NXP
2. Busca: LPC4000
3. Selecciona "NXP::LPC4000_DFP"
4. Click en "Install"
5. Espera a que descargue e instale (50-100 MB)
```

#### 2.3 Verificar Pack

```text
1. En Pack Installer
2. Devices → NXP → LPC408x_7x → LPC4088
3. Debería aparecer como "installed"
```

### Paso 3: Instalar Drivers de Depuración

#### 3.1 CMSIS-DAP (Incluido en Keil)

Los drivers CMSIS-DAP se instalan automáticamente con Keil µVision.

#### 3.2 J-Link (Alternativo)

Si usas un J-Link externo:

```text
1. Descarga de: www.segger.com/downloads/jlink
2. Selecciona "J-Link Software and Documentation Pack"
3. Instala el paquete completo
4. Reinicia el PC si se solicita
```

### Paso 4: Instalar Herramientas Adicionales

#### 4.1 Git para Windows

```bash
# Descargar de: https://git-scm.com/download/win
# Durante la instalación:
# - Usar editor recomendado
# - Añadir Git a PATH
# - Usar OpenSSH
```

#### 4.2 Terminal Serie (PuTTY)

```text
1. Descarga de: www.putty.org
2. Ejecuta el instalador
3. Instalación estándar
```

#### 4.3 Doxygen (Opcional)

```text
1. Descarga de: www.doxygen.nl/download.html
2. Instala Doxygen
3. Opcionalmente instala GraphViz para diagramas
```

## Configuración del Hardware

### Paso 1: Desempaquetar la Developer's Kit

```text
1. Saca cuidadosamente la tarjeta del embalaje antiestático
2. Verifica que incluya:
   - Tarjeta base OEM Board
   - Pantalla LCD conectada
   - Cable USB
   - (Opcional) Accesorios adicionales
```

### Paso 2: Inspección Visual

Verifica:

- [ ] No hay componentes dañados
- [ ] Conectores intactos
- [ ] Pantalla LCD firmemente conectada
- [ ] No hay cortocircuitos visibles

### Paso 3: Primera Conexión

#### 3.1 Conectar USB

```text
1. Localiza el conector USB "CMSIS-DAP" en la tarjeta
2. Conecta el cable USB Mini-B
3. Conecta el otro extremo al PC
4. El LED de alimentación debería encenderse
```

#### 3.2 Instalación de Drivers

```text
Windows debería detectar el dispositivo automáticamente:
1. "CMSIS-DAP" - Para depuración
2. Puerto COM virtual - Para UART (si está configurado)

Si no se instalan automáticamente:
1. Abre Administrador de Dispositivos
2. Busca dispositivos con signo de exclamación
3. Click derecho → Actualizar driver
4. Buscar automáticamente
```

### Paso 4: Verificar Conexión

#### En Keil µVision

```text
1. Flash → Configure Flash Tools
2. Pestaña "Debug"
3. Selecciona "CMSIS-DAP Debugger"
4. Click en "Settings"
5. En "SW Device" debería aparecer el LPC4088
6. Si aparece, la conexión es correcta
```

## Configuración de Keil µVision

### Paso 1: Configuración General

#### 1.1 Preferencias

```text
Edit → Configuration
```

**Editor:**

```text
[Editor]
- Tab Size: 4
- Insert Spaces: ✓
- Auto Indent: ✓
- Show Line Numbers: ✓
- Font: Courier New, 10pt
```

**Colors:**

```text
[Colors & Fonts]
- Scheme: Personalizar o usar "Visual Studio Dark"
```

**Directories:**

```text
[Folders/Extensions]
- Output: .\Objects
- Listing: .\Listings
```

### Paso 2: Configuración de Proyecto Tipo

#### 2.1 Opciones de Target

```text
Project → Options for Target (Alt+F7)
```

**Device:**

```text
[Device]
Device: NXP LPC4088FBD208
```

**Target:**

```text
[Target]
Xtal (MHz): 12.0
Use On-chip ROM: ✓
Use On-chip RAM: ✓
```

**Output:**

```text
[Output]
Name of Executable: proyecto.axf
Create HEX File: ✓
Browse Information: ✓
```

**Listing:**

```text
[Listing]
Generate Map File: ✓ (opcional)
```

#### 2.2 Opciones de C/C++

```text
[C/C++]
Optimization: -O1 (para desarrollo) o -O2 (producción)
Warnings: All Warnings
Language C: c99
Misc Controls: -Wextra
```

**Define:**

```text
Define:
ARM_MATH_CM4
__FPU_PRESENT=1
```

**Include Paths:**

```text
Include Paths:
.\
.\Librerias
```

#### 2.3 Opciones de Debug

```text
[Debug]
Use: CMSIS-DAP Debugger

Settings → Debug:
- Port: SW
- Max Clock: 10 MHz
- Connect: Normal
- Reset: SYSRESETREQ

Settings → Flash Download:
- Download Function: ✓
- Erase Full Chip: ✓ (primera vez)
- Erase Sectors: ✓ (normal)
- Reset and Run: ✓
- Verify: ✓
```

## Primer Proyecto

### Método 1: Usar un Proyecto Existente

#### 1.1 Clonar el Repositorio

```bash
# En Git Bash o PowerShell
cd C:\
git clone https://github.com/ale87jan/LPC4088-Documentacion.git
```

O descargar ZIP desde GitHub y extraer.

#### 1.2 Abrir el Workspace

```text
1. Abre Keil µVision
2. File → Open Project
3. Navega a: C:\GitHub\LPC4088-Documentacion\Librerias\
4. Abre: 00_Librerias.uvmpw (workspace completo)
   O abre directamente: 01_GLCD.uvprojx
```

#### 1.3 Compilar

```text
1. Project → Build Target (F7)
2. Revisa la ventana "Build Output"
3. Debería ver: "0 Error(s), 0 Warning(s)"
```

#### 1.4 Programar

```text
1. Flash → Download (F8)
2. Espera a que complete
3. Mensaje: "Application running..."
```

#### 1.5 Depurar

```text
1. Debug → Start/Stop Debug Session (Ctrl+F5)
2. Debug → Run (F5)
3. El programa debería ejecutarse en el hardware
4. Observa la pantalla LCD
```

### Método 2: Crear Proyecto Nuevo

#### 2.1 Crear Proyecto

```text
1. Project → New µVision Project
2. Nombre: mi_proyecto
3. Ubicación: C:\Proyectos\LPC4088\mi_proyecto\
4. Guardar
```

#### 2.2 Seleccionar Dispositivo

```text
1. Device: NXP → LPC408x_7x → LPC4088FBD208
2. OK
```

#### 2.3 Manage Run-Time Environment

```text
Se abre automáticamente. Selecciona:

CMSIS:
✓ CORE

Device:
✓ Startup

Click "OK"
```

#### 2.4 Agregar Archivos

```text
1. Project → Manage → Project Items (Alt+F7)
2. Groups: Click "New (Insert)"
3. Nombre: "Source"
4. Files: Click "Add Files"
5. Navega a las librerías necesarias
6. Agrega: glcd.c, gpio_lpc40xx.c, etc.
```

#### 2.5 Crear main.c

```text
1. File → New
2. Guardar como: main.c
3. Agregar al proyecto
```

#### 2.6 Código de Prueba

```c
#include "LPC407x_8x_177x_8x.h"
#include "glcd.h"

int main(void) {
    // Configuración del sistema
    SystemCoreClockUpdate();
    
    // Inicializar LCD
    GLCD_Init();
    GLCD_Clear(GLCD_COLOR_BLACK);
    
    // Mostrar texto
    GLCD_SetFont(&font_16x32);
    GLCD_PutString(100, 100, "Hola LPC4088!", 
                   GLCD_COLOR_WHITE, GLCD_COLOR_BLACK);
    
    // Bucle infinito
    while (1) {
        // Tu código aquí
    }
}
```

#### 2.7 Configurar Proyecto

Sigue los pasos de [Configuración de Proyecto](#paso-2-configuración-de-proyecto-tipo).

#### 2.8 Compilar y Probar

```text
1. Build (F7)
2. Download (F8)
3. Debug (Ctrl+F5)
4. Run (F5)
```

### Verificar Funcionamiento

Si todo está correcto deberías ver:

- ✅ La pantalla LCD muestra "Hola LPC4088!"
- ✅ No hay errores en la ventana de debug
- ✅ El programa responde correctamente

## Solución de Problemas

### Problema: No se Detecta el Dispositivo

**Síntomas:**

- "No CMSIS-DAP device found"
- No aparece en configuración de debug

**Soluciones:**

```text
1. Verifica la conexión USB:
   - Cable conectado firmemente
   - LED de alimentación encendido
   - Usa otro puerto USB

2. Reinstala drivers:
   - Desinstala dispositivo en Administrador
   - Desconecta y reconecta USB
   - Deja que Windows reinstale

3. Verifica en Administrador de Dispositivos:
   - Busca "CMSIS-DAP" o "LPC"
   - Si tiene signo !, actualiza driver

4. Prueba otro cable USB:
   - Algunos cables solo cargan, no transfieren datos
```

### Problema: Error al Compilar

**Síntomas:**

- Errores de "file not found"
- Undefined reference

**Soluciones:**

```text
1. Verifica Include Paths:
   - Project → Options → C/C++ → Include Paths
   - Agrega rutas necesarias

2. Verifica que los archivos estén agregados:
   - Project → Manage → Project Items
   - Agrega archivos .c faltantes

3. Verifica Device Pack:
   - Pack Installer
   - NXP LPC4000 debe estar instalado

4. Limpia y recompila:
   - Project → Clean Targets
   - Project → Build Target
```

### Problema: Error al Programar

**Síntomas:**

- "Flash Download failed"
- "Could not load file"

**Soluciones:**

```text
1. Verifica configuración de Flash:
   - Options → Debug → Settings
   - Flash Download debe estar habilitado

2. Reduce velocidad de reloj:
   - Debug Settings → Max Clock: 1 MHz
   - Intenta de nuevo

3. Erase completo:
   - Flash → Erase
   - Intenta programar nuevamente

4. Verifica alimentación:
   - LED encendido
   - Voltaje estable
   - Fuente externa si es necesario
```

### Problema: El Programa no Funciona

**Síntomas:**

- Pantalla en blanco
- No responde a entradas
- Comportamiento errático

**Soluciones:**

```text
1. Verifica inicialización:
   - SystemCoreClockUpdate() al inicio
   - Periféricos inicializados correctamente

2. Usa el debugger:
   - Coloca breakpoints
   - Verifica flujo del programa
   - Inspecciona variables

3. Verifica hardware:
   - Conexiones correctas
   - Voltajes adecuados
   - Componentes funcionando

4. Revisa configuración de reloj:
   - system_LPC407x_8x_177x_8x.c
   - Frecuencias correctas
```

### Problema: La Pantalla no Muestra Nada

**Síntomas:**

- LCD encendido pero negro
- No hay contenido visible

**Soluciones:**

```text
1. Verifica conexión de LCD:
   - Conectores firmemente insertados
   - Sin pines doblados

2. Verifica inicialización:
   - GLCD_Init() llamado
   - SDRAM_Init() si es necesario
   - Orden correcto de inicialización

3. Ajusta brillo:
   - Potenciómetro de retroiluminación
   - Control por PWM si aplica

4. Prueba código simple:
   - GLCD_Clear(GLCD_COLOR_WHITE);
   - Debería ver pantalla blanca
```

### Problema: UART no Funciona

**Síntomas:**

- No recibe datos
- No envía datos
- Caracteres incorrectos

**Soluciones:**

```text
1. Verifica configuración de terminal:
   - Baudrate correcto (típicamente 115200)
   - 8 bits de datos
   - Sin paridad
   - 1 bit de stop

2. Verifica el puerto COM:
   - Administrador de Dispositivos
   - Nota el número de COM
   - Úsalo en el terminal

3. Verifica inicialización UART:
   - UART_Init() con baudrate correcto
   - Pines configurados (IOCON)

4. Prueba loopback:
   - Conecta TX a RX
   - Deberías recibir lo que envías
```

## Recursos de Ayuda

### Documentación

- [NXP LPC4088 User Manual](https://www.nxp.com/) - Manual completo del chip
- [Keil µVision Documentation](https://www.keil.com/support/man/docs/uv4/) - Guía del IDE
- [ARM Cortex-M4 TRM](https://developer.arm.com/) - Referencia técnica

### Comunidad y Soporte

- **Foro de Keil:** [www.keil.com/forum](https://www.keil.com/forum)
- **GitHub Issues:** Para reportar problemas del proyecto
- **Email institucional:** [alejandro.lara@uca.es](mailto:alejandro.lara@uca.es)

### Tutoriales Adicionales

- [Getting Started with Keil](https://www.keil.com/support/man/docs/uv4/uv4_gs_overview.htm)
- [CMSIS Documentation](https://arm-software.github.io/CMSIS_5/)
- [ARM Development Studio](https://developer.arm.com/tools-and-software/embedded/arm-development-studio)

## Próximos Pasos

Una vez configurado el entorno:

1. ✅ **Explora los ejemplos** - Ver [EJEMPLOS.md](EJEMPLOS.md)
2. ✅ **Aprende las librerías** - Ver [LIBRERIAS.md](LIBRERIAS.md)
3. ✅ **Conoce el hardware** - Ver [HARDWARE.md](HARDWARE.md)
4. ✅ **Crea tu proyecto** - Experimenta y aprende
5. ✅ **Contribuye** - Ver [CONTRIBUTING.md](../CONTRIBUTING.md)

## Checklist de Instalación Completa

Marca cada ítem cuando esté completado:

### Software

- [ ] Keil µVision instalado y funcionando
- [ ] LPC4000 Device Pack instalado
- [ ] Drivers CMSIS-DAP funcionando
- [ ] Git para Windows instalado (opcional)
- [ ] Terminal serie instalado (PuTTY u otro)

### Hardware

- [ ] LPC4088 Developer's Kit conectada
- [ ] LED de alimentación encendido
- [ ] Dispositivo detectado en Windows
- [ ] Pantalla LCD funcionando

### Configuración

- [ ] Primer proyecto compilado sin errores
- [ ] Programa descargado exitosamente
- [ ] Aplicación ejecutándose en hardware
- [ ] Pantalla LCD mostrando contenido
- [ ] Debug session funcional

### Verificación Final

- [ ] Proyecto 01_GLCD funciona correctamente
- [ ] Puedo crear nuevos proyectos
- [ ] Comprendo la estructura del proyecto
- [ ] Tengo acceso a la documentación

Si todos los ítems están marcados, ¡estás listo para desarrollar con el LPC4088!

---

**¿Problemas?** Consulta la sección de [Solución de Problemas](#solución-de-problemas) o contacta para soporte.

---

<div align="center">
<!-- markdownlint-disable-next-line -->
**¡Bienvenido al desarrollo embebido con LPC4088! 🎉**

</div>
