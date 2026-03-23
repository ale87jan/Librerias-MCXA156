<!-- LICENSE INFORMATION
Copyright (C) 2026 Alejandro Lara Doña
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled "GNU
Free Documentation License".
-->

# Testing & Validation

- **Hardware-in-loop only**: Must test on physical LPC4088 kit
- **No unit tests**: Educational focus on observable behavior
- Verify via:
  - LCD output for graphics
  - Serial terminal (115200 baud) for UART
  - LED states for GPIO/interrupts
