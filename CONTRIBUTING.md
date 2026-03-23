<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Guía Rápida de Contribución

¡Gracias por tu interés en contribuir! Esta guía resume los pasos esenciales.
Para plantillas de issues/PRs, proceso de revisión y preguntas frecuentes,
consulta la [guía detallada](docs_plantilla/CONTRIBUCION.md).

## Formas de Contribuir

- Corregir errores en código o documentación
- Añadir nuevas librerías o ejemplos educativos
- Mejorar explicaciones y comentarios existentes
- Reportar bugs o proponer mejoras mediante
  [Issues](https://github.com/ale87jan/Librerias-MCXA156/issues)

## Flujo de Trabajo

### 1. Fork y Clone

```bash
git clone https://github.com/TU-USUARIO/Librerias-MCXA156.git
cd Librerias-MCXA156
```

### 2. Crear una Rama

| Prefijo      | Uso                                      |
|--------------|------------------------------------------|
| `feature/`   | Nueva librería o característica          |
| `fix/`       | Corrección de bug                        |
| `docs/`      | Cambios en documentación                 |
| `refactor/`  | Reestructuración sin cambios funcionales |

```bash
git checkout -b feature/nueva-libreria-xyz
```

### 3. Hacer Cambios

- Sigue el [estilo de código C](.claude/estiloC.md) del proyecto
- Documenta con [Doxygen](.claude/docDoxygen.md) todas las APIs públicas
- Prueba en hardware real (FRDM-MCXA156)

### 4. Commit

Formato: `tipo(alcance): descripción breve`

| Tipo       | Uso                                              |
|------------|--------------------------------------------------|
| `feat`     | Nueva característica o librería                  |
| `fix`      | Corrección de bug                                |
| `docs`     | Solo documentación                               |
| `style`    | Formato, sin cambio de lógica                    |
| `refactor` | Reestructuración sin cambio de comportamiento    |
| `test`     | Añadir o actualizar código de prueba             |
| `chore`    | Sistema de build, toolchain, archivos de proyecto|

```bash
git commit -m "feat(uart): añadir auto-detección de baud rate"
```

### 5. Push y Pull Request

```bash
git push origin feature/nueva-libreria-xyz
```

Crea un Pull Request en GitHub con título descriptivo y descripción de los
cambios. Consulta la
[plantilla de PR](docs_plantilla/CONTRIBUCION.md#plantilla-de-pull-request).

### Checklist antes de enviar

- [ ] Compila sin errores ni advertencias en Keil µVision (ARM Compiler 6)
- [ ] Probado en hardware FRDM-MCXA156
- [ ] Ejemplos existentes siguen funcionando
- [ ] Documentación Doxygen presente en APIs públicas
- [ ] Sin números mágicos — usar constantes con nombre

## Licencia

- **Código:** GNU General Public License v3.0 o posterior
- **Documentación:** GNU Free Documentation License v1.3 o posterior

## Más Información

- [Guía detallada de contribución](docs_plantilla/CONTRIBUCION.md) — plantillas,
  revisión, FAQ
- [Estilo de código C](.claude/estiloC.md)
- [Documentación Doxygen](.claude/docDoxygen.md)
- [Git workflow](.claude/git.md)

---

**¿Preguntas?** Contacta en [alejandro.lara@uca.es](mailto:alejandro.lara@uca.es)
o crea un [Issue](https://github.com/ale87jan/Librerias-MCXA156/issues).
