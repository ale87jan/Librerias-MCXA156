---
paths:
  - "Librerias/*.{c,h}"
---

# Estilo de C

## Code Rules (CRITICAL - Differs from Standard C)

- Compliant with C (GNU11) and C++ (GNU++11) or C (GNU17) and C++ (GNU++17).
- Uses ANSI C standard data types defined in **<stdint.h>**.
- Variables and parameters have a complete data type.
- Expressions for #define constants are enclosed in parenthesis.
- Conforms to MISRA 2012 (but does not claim MISRA compliance). MISRA rule violations are documented.

Namespace_ prefixes avoid clashes with user identifiers and provide functional groups (i.e. for peripherals, RTOS, or DSP Library).

## Violates the following MISRA-C:2012 rules

- **Directive 4.2**: All usage of assembly language should be documented. CMSIS-Core uses assembly statements to access core registers on several places. These locations start with `__ASM`. Inline assembly statements may be opaque to MISRA Checkers and can cause false-positive warnings.
- **Directive 4.9**: Function-like macro defined. Violated since function-like macros are used to generate more efficient code.
- **Rule 1.3**: Multiple use of '#/##' operators in macro definition. Violated since function-like macros are used to generate more efficient code.
- **Rule 11.4**: Conversion between a pointer and integer type. Violated because of core register access.
- **Rule 11.6**: Cast from unsigned long to pointer. Violated because of core register access.
- **Rule 13.5**: Side effects on right hand side of logical operator. Violated because of shift operand is used in macros and functions.
- **Rule 14.4**: Conditional expression should have essentially Boolean type. Violated since macros with several instructions are used.
- **Rule 15.5**: Return statement before end of function. Violated to simplify code logic.
- **Rule 20.10**: '#/##' operators used. Violated since function-like macros are used to generate more efficient code.
- **Rules 21.1 and 21.2**: Reserved to the compiler. Violated since macros with leading underscores are used.

### Naming (All in Spanish)

```c
// Functions: snake_case names with module prefix
void timer_inicializar(MCXA15X_TIM_t *timer_regs);
void uart_transmitir_dato(MCXA15X_UART_t *uart, uint8_t dato);

// Variables: snake_case, prefix 'g_' for globals
uint32_t contador_actual = 0;
volatile bool_t g_flag_timer = FALSE;

// Constants/Macros: UPPER_CASE
#define LED1_PIN (18u)
#define GLCD_PIXELES_POR_LINEA (480u)

// Constants: PascalCase with k preffix
#define kLed1Pin (18u)
#define kPiezaCuadrada (480u)

// Types: snake_case with _t suffix
typedef struct {
  uint8_t hora;
  uint8_t minuto;
} hora_t;
```

### Formatting (K&R with specific rules)

```c
// 100 character line width
// 2 SPACES indentation (NOT 4, NOT tabs)
// Opening brace same line for EVERYTHING (including functions)
void funcion_ejemplo(uint32_t parametro) {
  // Blank line after opening brace in functions (optional)
  if (condicion) {
    // code
  } else {
    // code
  }
}
```

## Declarations & Definitions

### Pointers

Asterisk next to the variable name, not the type:

```c
int16_t *ptr;   // Correct
int16_t* ptr;   // Wrong
```

### Constants — prefer `enum` over `#define`

`enum` constants appear in the symbol table (easier to debug), can be used as
`case` labels in `switch`, and occupy no memory. Use `#define` only when the
constant must be visible to the assembler preprocessor.

```c
typedef enum {
  kPiezaPalo,
  kPiezaCuadrado,
  kPiezaEse,
} pieza_tipo_t;
```

### Functions — `void` for no arguments

```c
bool_t mi_funcion(void);  // Correct — NOT mi_funcion()
```

### `static` declarations

`static` symbols must **not** appear in header files (`.h`). Headers define the
public interface; `static` definitions are copied, not shared, between
compilation units. Do not combine `static` + `inline`.

### Struct initialization — designated initializers

Always use explicit (designated) initializers when initializing `struct` or `union`:

```c
pieza_t mi_pieza = {
  .tipo   = kPiezaPalo,
  .tamano = 4,
  .color  = kRojo,
};
```

### Function-like macros

Avoid them when possible. When necessary, make them hygienic:

- Enclose every argument in parentheses.
- Do **not** end the macro with a semicolon.
- If it returns a value, wrap in a `({ ... })` block.
- If it does not return a value, wrap in `do { ... } while (0)`.

```c
// Returns value:
#define CEIL(x) \
({ \
  __typeof__(x) _x = (x); \
  (_x > 0) ? (long long)(_x + 0.9999999999) : (long long)_x; \
})

// No return value:
#define ASSERT(expr, msg) \
do { \
  if (!(expr)) { \
    parar_con_error(__FILE__, __FUNCTION__, __LINE__, msg); \
  } \
} while (0)
```

## Horizontal Spacing

```c
int16_t resultado = (a + b) * c;  // (1) space around binary operators; no space inside ()
v = w*x + y/z;                    // (1) may omit around * / in expressions
mi_funcion(arg1, arg2);           // (2) no space before '('; (3) space after ','
mi_funcion(arg1, arg2) {          // (4) 1 space before '{'
a = 0;  // (5) 2 spaces before end-of-line comment
for (i = 0; i < 5; i++) {        // (6) space after ';' in for
switch (i) {
  case 1:                         // (7) no space before ':' in switch
    // ...
}
```

## Infinite Loops

Prefer `while (1)` or `while (true)` instead of `for (;;)`.

## Common Pitfalls

1. **NEVER use tabs**: Configure editor for 2-space indentation.
2. **Include order matters**: Main module header (for library implementation) -> System #includes (e.g., `<stdint.h>`) -> Peripheral headers -> Local/Private headers.
