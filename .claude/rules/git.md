# Git Workflow

## Commit Convention

Format: `type(scope): brief description` (max 72 characters for the subject line)

Optionally, add a blank line followed by a more detailed body.

### Commit Types

| Type       | Use for                                          |
|------------|--------------------------------------------------|
| `feat`     | New feature or new library                       |
| `fix`      | Bug fix                                          |
| `docs`     | Documentation only (Doxygen, Markdown, comments) |
| `style`    | Formatting, missing semicolons — no logic change |
| `refactor` | Code restructure with no behavior change         |
| `test`     | Adding or updating hardware test code            |
| `chore`    | Build system, toolchain, project files           |

### Scope

Use the peripheral or module name as scope when applicable (e.g., `uart`, `gpio`, `glcd`, `rtc`).

**Examples:**

```
feat(uart): add baud rate auto-detection
fix(gpio): correct pull-up register mask for port 3
docs(spi): add Doxygen @param for spi_transferir()
refactor(adc): extract channel validation into helper
```

---

## Branch Naming

| Prefix        | Use for                        |
|---------------|--------------------------------|
| `feature/`    | New library or feature         |
| `fix/`        | Bug correction                 |
| `docs/`       | Documentation changes only     |
| `refactor/`   | Restructuring without new code |

Example: `feature/i2c-driver`, `fix/uart-overflow`, `docs/glcd-api`

---

## Pull Request Requirements

Before opening a PR, verify:

- [ ] Compiles without errors or warnings in Keil µVision (ARM Compiler 6)
- [ ] Tested on physical FRDM-MCXA156 hardware
- [ ] Existing examples still build and run correctly
- [ ] Doxygen blocks present for all public API functions
- [ ] No magic numbers — use named constants

PRs require at least one reviewer approval before merging.
**Never force-push to `main`.**

---

## License Headers

Every new source file must include a license header comment:

- **C/H files** → GNU General Public License v3.0 or later
- **Markdown docs** → GNU Free Documentation License v1.3 or later

Refer to `CONTRIBUTING.md` for the full header templates.
