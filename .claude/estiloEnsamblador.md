<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Estilo para Ensamblador ARM

## Formato de Cuatro Columnas

| Columna | Regla |
|---------|-------|
| Etiquetas | Al inicio de la línea, terminadas en `:` |
| Mnemónicos | Indentados 4 espacios (`MOV`, `LDR`, `BEQ`…) |
| Operandos | Registros y valores inmediatos |
| Comentarios | Empiezan con `;` ; explican el **porqué**, no el qué |

```asm
esperar_bandera:
    LDR r1, [r0, #0x04]   ;@ Carga el registro de estado desde la base R0
    TST r1, #0x10         ;@ Comprueba si el bit 4 está activo
    BEQ esperar_bandera   ;@ Si es cero, vuelve a esperar
```

## Nomenclatura de Registros

Usa los nombres simbólicos definidos en la AAPCS: `sp`, `lr`, `pc`, etc.

## Comentario de Bloque (antes de cada función)

Describe propósito, registros de entrada/salida y registros que se modifican.

```asm
;==================================================================================================
; @file    b32_calcular_suma.S (b32/b64 según el compilador utilizado)
; @brief   Suma los valores de R0 y R1 y devuelve el resultado
;
; @author  Nombre Apellidos [EMAIL]
; @date    yyyy-mm-dd
; @version v1.0
;==================================================================================================

; --- Macros para mejorar la legibilidad ---
%define PARAM1   [ebp + 8]
%define PARAM2   [ebp + 12]

; --- Símbolo global ---
; En x86-32, so compilas en Linux, NO se usa prefijo '_'.
    global  _b32_calcular_suma
    section .text

;--------------------------------------------------------------------------------------------------
; int32_t mi_funcion(int32_t param1, int32_t param2)
;
; @param[in]  R0 = primer operando
; @param[in]  R1 = segundo operando
; @param[out] R0 = suma
;--------------------------------------------------------------------------------------------------

_b32_calcular_suma:
    ; Prólogo
    push    ebp             ; Guardar EBP del llamador
    movaps  ebp, esp        ; Establecer marco de pila propio

    ; Preservar registros callee-saved que se vayan a usar (si aplica)
    ; push  ebx
    ; push  esi
    ; push  edi

    ; Cuerpo
    ; TODO: implementar la lógica del ejercicio.
    mov     eax, PARAM1     ; eax ← param1
    add     eax, PARAM2     ; eax ← eax + param2

    ; El valor de retorno queda en EAX al llegar al epílogo.

    ; Epílogo
    ; Restaurar registros callee-saved en orden inverso (si se guardaron)
    ; pop   edi
    ; pop   esi
    ; pop   ebx

    pop     ebp             ; Restaurar EBP del llamador
    ret                     ; Retornar (dirección de retorno en [esp])
```
