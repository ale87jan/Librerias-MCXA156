---
paths:
  - "Librerias/**/*.{s,S,asm}"
---

# Estilo para Ensamblador ARM

Las reglas de formato están codificadas en `.editorconfig` (raíz del repositorio). El editor debe respetarlas automáticamente; no sobreescribas esa configuración.

## Formato de Cuatro Columnas

| Columna | Regla |
| ------- | ----- |
| Etiquetas | Al inicio de la línea, terminadas en `:` |
| Mnemónicos | Indentados 4 espacios (`MOV`, `LDR`, `BEQ`, …) |
| Operandos | Registros y valores inmediatos |
| Comentarios | Empiezan con `;`. Explican el **porqué**, no el qué |

```asm
esperar_bandera:
    LDR r1, [r0, #0x04]   ; Carga el registro de estado desde la base R0
    TST r1, #0x10         ; Comprueba si el bit 4 está activo
    BEQ esperar_bandera   ; Si es cero, vuelve a esperar
```

## Nomenclatura de Registros

Usa los nombres simbólicos definidos en la AAPCS: `sp`, `lr`, `pc`, etc.

## Plantilla - Comentarios y Documentación

Describe propósito, registros de entrada/salida y registros que se modifican.

```asm
; =================================================================================================
; @file  plantilla_arm.s
; @brief Descripción breve del propósito del archivo y su funcionalidad.
; Por ejemplo: "Plantilla en ensamblador para Cortex-M4 con uso de constantes, datos de solo lectura
; y alias de registros"
;
; @author  Nombre Apellidos [EMAIL]
; @date    yyyy-mm-dd
; @version v1.0
; =================================================================================================

; === Definiciones de Constantes (EQU) ===
; Usamos EQU para valores que no cambian
DATO_EQU EQU 0x10000099   ; Ejemplo de constante definida con .equ (valor de 32 bits)

; === Sección de Datos (Read-Only) ===
; ALINEACIÓN: Es recomendable alinear las constantes a 4 bytes (32 bits), aunque no es
; obligatorio para datos de 8 o 16 bits. Asegura que el acceso a estas constantes sea
; eficiente y compatible con las instrucciones de carga de 32 bits (LDR) que se utilizan para
; acceder a ellas. Si no se alinea correctamente, el ensamblador puede generar código
; adicional para manejar accesos a direcciones no alineadas, afectando al rendimiento.
    AREA    CONSTANTES, DATA, READONLY
    ALIGN   4               ; Alineación a 4 bytes. Equivalente a .align 2 (2^2 = 4 bytes)
    EXPORT  DATO_RO         ; Convierte en "global" la etiqueta indicada para que sea visible
                            ; desde otras partes del programa (como C) y enlazadores (linkers)

DATO_RO DCW 0x2100          ; Ejemplo de un dato halfword de solo lectura (16 bits)

; === Configuración de la sección de código ===
; - ALINEACIÓN: Para código en modo Thumb-2, es obligatorio alinear a 16 bits (2 bytes) como
;   mínimo, aunque se recomienda alinear a 32 bits (4 bytes) para mejorar el rendimiento.
; - MODO THUMB: La directiva .thumb es esencial para indicar que el código está escrito para
;   ejecutarse en modo Thumb, que es el modo de operación de los Cortex-M4.
    AREA    |.text|, CODE, READONLY
    ALIGN   4               ; Alineación a 4 bytes
    THUMB                   ; Modo Thumb para Cortex-M4

    EXPORT  plantilla_arm   ; Hace la función visible desde C

; -------------------------------------------------------------------------------------------------
; uint32_t plantilla_arm(uint32_t dato);
;
; @brief Descripción breve de la función, por ejemplo: "Ejemplo de función en ensamblador que 
; realiza operaciones con constantes y datos de solo lectura"
;
; @note Es un ejemplo de uso de
;
; - Constantes definidas con EQU
; - Constantes almacenadas en la sección `READONLY`
; - Uso de alias de registros con ALIAS para mejorar la legibilidad
; - Convención de llamada AAPCS para funciones en ARM
; - Programación de instrucciones en ensamblador
; - Prólogo y epílogo estándar para preservar registros callee-saved
;
; CONVENCIÓN DE LLAMADA (AAPCS):
;
; - Entradas: r0 = param1, r1 = param2, r2 = param3, r3 = param4
; - Salida:   r0 = resultado de la función
; - Registros Callee-saved (preservar): r4 a r11
; - Registros Caller-saved (libres):    r0 a r3, r12

; === Alias de Registros (RN) ===
; Mejoran la legibilidad del código. Permiten usar nombres descriptivos en lugar de números de
; registro, lo que facilita la comprensión del propósito de cada registro. No es obligatorio, pero
; sí recomendable para código más complejo.
; Los registros r0-r3 se usan para los parámetros de entrada y la salida. Si no se utilizan tantos
; parámetros se pueden utilizar con otro fines y definir otros alias adecuados para ellos.

DATO            RN  r0  ; Registro que contiene el primer parámetro de la función
SALIDA          RN  r0  ; Registro de retorno que contiene el resultado de la función
                        ; Se puede utilizar varios alias para el mismo registro si fuese necesario
REG_DATO_EQU    RN  r1  ; Registro para cargar el valor de DATO_EQU
PTR_DATO_RO     RN  r2  ; Registro para cargar la dirección de DATO_RO
REG_DATO_RO     RN  r3  ; Registro para cargar el valor de DATO_RO
ACUMULADOR      RN  r4  ; Registro para almacenar resultados intermedios

plantilla_arm PROC
    ; === PRÓLOGO ===
    ; Si se utilizan registros `callee-saved` (r4-r11), inclúyelos aquí
    push    {r4-r11}

    ; === CUERPO DE LA FUNCIÓN ===
    ; TODO: implementar la lógica del ejercicio
    
    ; --- EJEMPLO ---
    ; Para cargar constantes definidas con EQU, como DATO_EQU, es conveniente utilizar LDR por su
    ; flexibilidad. Dado que DATO_EQU es una constante de 32 bits, el ensamblador no puede
    ; codificarla directamente como un operando inmediato en la mayoría de las instrucciones
    ; (inm5/inm8). Esto impide su uso directo con instrucciones como ADD o MOV.
    ; Además, LDR permite que el ensamblador gestione la ubicación de la constante en memoria, lo
    ; que puede optimizar el acceso a ella y evitar problemas de codificación de operandos
    ; inmediatos.
    ldr     REG_DATO_EQU, =DATO_EQU    ; REG_DATO_EQU = r1 = Valor de DATO_EQU

    ; Cargamos los datos desde la zona de datos de solo lectura (rodata) usando LDR. El símbolo
    ; de la etiqueta se resuelve a la dirección de memoria donde se encuentra la constante, y el
    ; LDR posterior carga el valor de esa dirección en el registro.
    ldr     PTR_DATO_RO, =DATO_RO       ; PTR_DATO_RO = r2 = dirección de DATO_RO
    ldrh    REG_DATO_RO, [PTR_DATO_RO]  ; REG_DATO_RO = DATO_RO
                                        ; Usamos LDRH porque es un halfword (16 bits)

    add     ACUMULADOR, DATO, REG_DATO_EQU  ; ACUMULADOR = r4 = DATO + DATO_EQU
    add     SALIDA, ACUMULADOR, REG_DATO_RO ; SALIDA = ACUMULADOR + DATO_RO
    ; --- FIN EJEMPLO ---

    ; === EPÍLOGO ===
    ; Restaurar los registros `callee-saved` guardados
    pop {r4-r11}
    
    bx  lr  ; Retorna al llamador

    ENDP    ; Fin de la función plantilla_arm
    END     ; Fin del archivo de código fuente
```
