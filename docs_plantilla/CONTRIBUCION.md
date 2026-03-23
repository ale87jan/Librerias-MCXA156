<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Guía Detallada de Contribución

Este documento complementa la [guía rápida de contribución](../CONTRIBUTING.md)
con plantillas, procesos de revisión y preguntas frecuentes.

## Tabla de Contenidos

- [Código de Conducta](#código-de-conducta)
- [Reportar Errores](#reportar-errores)
- [Sugerir Mejoras](#sugerir-mejoras)
- [Plantilla de Pull Request](#plantilla-de-pull-request)
- [Documentación](#documentación)
- [Testing](#testing)
- [Proceso de Revisión](#proceso-de-revisión)
- [Preguntas Frecuentes](#preguntas-frecuentes)

## Código de Conducta

Este proyecto se adhiere a principios de respeto y colaboración. Se espera que
todos los contribuyentes:

- Sean respetuosos con otros contribuyentes
- Acepten críticas constructivas
- Se enfoquen en lo que es mejor para el proyecto educativo
- Mantengan un ambiente acogedor para estudiantes y educadores

## Reportar Errores

### Antes de Reportar

1. **Verifica que sea realmente un error**
   - Revisa la documentación
   - Verifica que estés usando la versión correcta
   - Asegúrate de que el hardware esté correctamente conectado

2. **Busca si ya fue reportado**
   - Revisa los [Issues](https://github.com/ale87jan/Librerias-MCXA156/issues)
     existentes
   - Incluye issues cerrados en tu búsqueda

### Plantilla de Issue (Bug)

```markdown
## Descripción del Error

[Descripción clara y concisa del error]

## Para Reproducir

Pasos para reproducir el comportamiento:
1. Compilar proyecto '...'
2. Ejecutar función '...'
3. Observar error '...'

## Comportamiento Esperado

[Descripción de lo que debería ocurrir]

## Comportamiento Actual

[Descripción de lo que realmente ocurre]

## Capturas de Pantalla

[Si aplica, añade capturas]

## Entorno

- Versión de Keil µVision: [ej. 5.39]
- Versión del compilador ARM: [ej. 6.19]
- Sistema Operativo: [ej. Windows 11]
- Hardware: [ej. FRDM-MCXA156]

## Código Relevante

~~~c
// Pega aquí el código relevante
~~~

## Información Adicional

[Cualquier otra información relevante]
```

## Sugerir Mejoras

### Plantilla de Feature Request

```markdown
## Descripción de la Característica
[Descripción clara y concisa de la característica deseada]

## Motivación
[¿Por qué sería útil esta característica?]

## Solución Propuesta
[Descripción de cómo debería funcionar]

## Alternativas Consideradas
[Otras formas de lograr el mismo objetivo]

## Contexto Educativo
[¿Cómo beneficiaría esto a los estudiantes?]

## Información Adicional
[Cualquier otra información relevante]
```

## Plantilla de Pull Request

```markdown
## Descripción
[Descripción de los cambios realizados]

## Tipo de Cambio
- [ ] Corrección de bug
- [ ] Nueva característica
- [ ] Breaking change
- [ ] Documentación

## ¿Cómo se ha Probado?
[Describe las pruebas realizadas]

## Checklist
- [ ] Mi código sigue las convenciones del proyecto
- [ ] He comentado mi código adecuadamente
- [ ] He actualizado la documentación correspondiente
- [ ] Mis cambios no generan nuevas advertencias
- [ ] He probado en hardware real
- [ ] Los cambios son compatibles con el código existente

## Issues Relacionados
Closes #123
Fixes #456

## Capturas (si aplica)
```

## Documentación

### Documentación en Código

- Usa comentarios Doxygen para todas las APIs públicas
- Explica algoritmos complejos
- Documenta casos especiales y limitaciones
- Incluye ejemplos de uso cuando sea útil

### Documentación Externa

Al modificar funcionalidad, actualiza:

- `README.md` — si afecta la descripción general
- `docs/LIBRERIAS.md` — si modificas o añades librerías
- `docs/EJEMPLOS.md` — si añades o modificas ejemplos
- `docs/HARDWARE.md` — si afecta especificaciones de hardware

### Documentación Educativa

Este es un proyecto educativo, así que:

- Explica conceptos que los estudiantes puedan no conocer
- Proporciona referencias a material de aprendizaje
- Incluye diagramas cuando ayuden a la comprensión
- Añade ejemplos progresivos (de simple a complejo)

## Testing

### Pruebas Requeridas

Antes de enviar un PR, asegúrate de:

1. **Compilación exitosa**
   - Sin errores
   - Sin advertencias (o justificadas)

2. **Prueba en hardware real**
   - Verifica en la FRDM-MCXA156
   - Prueba todos los casos de uso
   - Verifica casos límite

3. **No romper funcionalidad existente**
   - Prueba ejemplos relacionados
   - Verifica compatibilidad

### Reportar Resultados de Pruebas

```markdown
## Pruebas Realizadas

### Compilación
- [x] Compila sin errores
- [x] Compila sin advertencias

### Hardware
- [x] Probado en FRDM-MCXA156
- [x] Funciona correctamente con...
- [x] Casos límite verificados

### Compatibilidad
- [x] Ejemplos existentes funcionan correctamente
- [x] No rompe APIs existentes
```

## Proceso de Revisión

### Qué Esperamos

Los revisores verificarán:

1. **Corrección** — ¿El código hace lo que dice?
2. **Calidad** — ¿Sigue los estándares?
3. **Claridad** — ¿Es comprensible?
4. **Documentación** — ¿Está bien documentado?
5. **Tests** — ¿Fue probado adecuadamente?
6. **Valor educativo** — ¿Ayuda a los estudiantes?

### Después de la Revisión

- Responde a los comentarios
- Haz los cambios solicitados
- Solicita re-revisión
- Sé receptivo al feedback

## Preguntas Frecuentes

### ¿Puedo contribuir si soy estudiante?

¡Absolutamente! Las contribuciones de estudiantes son especialmente valiosas
porque:

- Sabes qué es confuso y necesita mejor explicación
- Puedes aportar perspectiva fresca
- Es una excelente forma de aprender

### ¿Necesito experiencia previa con Git?

No es necesario ser experto, pero deberías conocer:

- Cómo hacer fork de un repositorio
- Commits básicos
- Crear pull requests

Hay muchos tutoriales excelentes en línea.

### ¿Qué pasa si mi PR es rechazado?

- No te desanimes
- Pide feedback específico
- Aprende de los comentarios
- Intenta de nuevo con mejoras

### ¿Puedo trabajar en un issue sin asignación previa?

Sí, pero:

- Comenta en el issue que estás trabajando en él
- Para cambios grandes, discute el enfoque primero
- Revisa si alguien más ya está trabajando en ello

### ¿Cómo puedo empezar?

Busca issues etiquetados con:

- `good first issue` — buenos para principiantes
- `help wanted` — necesitan colaboradores
- `documentation` — mejoras de documentación
- `bug` — correcciones de errores

## Licencia

Al contribuir, aceptas que tus contribuciones sean licenciadas bajo la misma
licencia que el proyecto:

- **Código:** GNU General Public License v3.0 o posterior
- **Documentación:** GNU Free Documentation License v1.3 o posterior
