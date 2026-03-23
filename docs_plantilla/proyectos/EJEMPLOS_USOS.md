## Cómo Usar los Ejemplos

### Abrir un Proyecto

1. Abre Keil µVision
2. File → Open Project
3. Navega a `Librerias/`
4. Selecciona el archivo `.uvprojx` deseado

### O Usar el Workspace Completo

1. Abre Keil µVision
2. File → Open Project
3. Selecciona `Librerias/00_Librerias.uvmpw`
4. En el panel de proyectos, haz clic derecho en el proyecto deseado
5. Set as Active Project

### Compilar y Programar

1. **Compilar:** F7 o Build → Build Target
2. **Programar:** F8 o Flash → Download
3. **Depurar:** Ctrl+F5 o Debug → Start/Stop Debug Session
4. **Ejecutar:** F5 cuando estés en modo debug

### Modificar los Ejemplos

Cada ejemplo está diseñado para ser modificado y experimentado:

1. Lee el código en `main_*.c`
2. Revisa los comentarios y documentación
3. Modifica parámetros y comportamientos
4. Recompila y prueba
5. Experimenta con diferentes valores

### Crear Tu Propio Proyecto

#### Opción 1: Copiar un Proyecto Base

1. Copia la carpeta de un proyecto existente
2. Renombra los archivos `.uvprojx` y `.uvoptx`
3. Abre el proyecto en Keil
4. Modifica `main.c` según tus necesidades

#### Opción 2: Crear desde Cero

1. File → New → µVision Project
2. Selecciona el dispositivo: NXP → LPC408x_7x → LPC4088FBD208
3. Agrega los archivos de librerías necesarios
4. Configura las opciones del proyecto
5. Escribe tu código

### Estructura Típica de un Main

```c
#include "LPC407x_8x_177x_8x.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
// ... más includes

// Variables globales
volatile bool_t flag_timer = FALSE;

// Manejador de interrupción del timer
void TIMER0_IRQHandler(void) {
    if (TIMER0->IR & 0x01) {
        TIMER0->IR = 0x01;  // Limpiar flag
        flag_timer = TRUE;
    }
}

int main(void) {
    // Inicialización del sistema
    SystemCoreClockUpdate();

    // Inicializar periféricos
    GLCD_Init();
    TIMER_Init(TIMER0, 1);
    JOYSTICK_Init();

    // Configurar timer para 100ms
    TIMER_SetMatch(TIMER0, 0, 100000);
    TIMER_Start(TIMER0);

    // Pantalla inicial
    GLCD_Clear(GLCD_COLOR_BLACK);
    GLCD_PutString(10, 10, "Mi Proyecto",
                   GLCD_COLOR_WHITE, GLCD_COLOR_BLACK);

    // Bucle principal
    while (1) {
        if (flag_timer) {
            flag_timer = FALSE;

            // Tu código aquí (cada 100ms)
            uint8_t joy = JOYSTICK_Read();
            if (joy == JOYSTICK_ARRIBA) {
                // Hacer algo
            }
        }
    }
}
```
