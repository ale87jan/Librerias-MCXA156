---
description: Siempre usar mcp__markitdown__convert_to_markdown para acceder a URLs y archivos de formatos binarios o web
paths:
  - "**"
---

# Markitdown: contenido externo

**OBLIGATORIO** usar `mcp__markitdown__convert_to_markdown` para URLs `http/https` y archivos locales: `.pdf`, `.docx`, `.doc`, `.epub`, `.pptx`, `.ppt`, `.xlsx`, `.xls`, `.csv`, `.json`, `.xml`, `.jpg`, `.jpeg`, `.png`, `.gif`, `.bmp`, `.webp`, `.wav`, `.mp3`, `.zip`.

Para archivos locales usar URI `file:///ruta/absoluta`.

**Excepcion**: APIs REST que devuelven JSON (ej. CrossRef, metadatos bibliograficos) -> usar `WebFetch`.
