# STM32F411CEUx Bare-Metal Peripheral Drivers

> [!NOTE]
> **AI Usage Disclaimer:**  
> All peripheral driver logic, register configurations, and source code in this repository have been written **manually from scratch (bare-metal)** by the developer for educational purposes. Artificial intelligence was **not used for code generation or automated coding**. It was solely consulted as a technical reference/tutor for conceptual questions, standardizing Doxygen function comments, and structuring this documentation.

---

## 📌 Project Overview

This repository is an educational project focused on learning and implementing **bare-metal peripheral driver development from scratch** on the **STM32F411CEU6 (ARM® Cortex®-M4)** microcontroller.

Rather than relying on high-level vendor abstraction layers (such as STM32Cube HAL or LL), each driver is constructed directly by analyzing the microcontroller's **Reference Manual (RM0383)**, **Datasheet**, and **ARM Cortex-M4 Generic User Guide**. The goal is to gain an in-depth understanding of register-level hardware programming, memory-mapped I/O, peripheral bus architectures, and interrupt controllers.

---

## 🛠️ Hardware & Toolchain

* **Target MCU:** STM32F411CEU6 (WeAct Black Pill)
  * Core: ARM® 32-bit Cortex®-M4 with FPU @ 100 MHz max
  * Memory: 512 KB Flash, 128 KB SRAM
* **Compiler / Toolchain:** `arm-none-eabi-gcc` (GNU Arm Embedded Toolchain)
* **Build System:** CMake & Ninja
* **CMSIS:** Minimal inclusion for core processor register definitions and NVIC helper interfaces.

---

## 🚀 Current Implementation Status

### 🟢 GPIO Driver (`stm32f411xx_gpio_driver`)
- [x] **Peripheral Clock Control:** Enable / disable clock gating for GPIO ports A through H via `RCC->AHB1ENR`.
- [x] **Pin Modes:** Input, Output, Alternate Function (AF0–AF15), and Analog mode configurations.
- [x] **Output Types & Speeds:** Push-Pull vs. Open-Drain configurations and 4 selectable slew rate/speed levels (`OSPEEDR`).
- [x] **Pull-up / Pull-down Resistors:** Configurable internal Pull-up, Pull-down, and floating (No-PUPD) states.
- [x] **Data I/O Operations:** Atomic pin read, 16-bit port read, pin write, 16-bit port write, and pin toggling.
- [x] **External Interrupts (EXTI & NVIC):**
  - Configurable edge detection: Falling Edge, Rising Edge, and Concurrent Rising/Falling Edge triggers.
  - Port-to-line multiplexing using `SYSCFG->EXTICR`.
  - Core interrupt management using ARM Cortex-M NVIC (`NVIC_EnableIRQ`, `NVIC_DisableIRQ`, `NVIC_SetPriority`).
  - Safe, race-condition-free pending flag clearance mechanism for `EXTI->PR` (`rc_w1`).

### 🟢 SysTick Timer Driver (`stm32f411xx_systick_driver`)
- [x] **1 ms Time Base:** Precise 1 ms millisecond time base using ARM Cortex-M4 internal 24-bit SysTick down-counter.
- [x] **Clock Awareness:** Dynamically synchronized with `SystemCoreClock` (16 MHz HSI default or PLL).
- [x] **Non-Blocking Millisecond Counter:** Global millisecond tracking (`SysTick_Get_Ms()`) via `SysTick_Handler` interrupt for timestamping and delta-time measurements without CPU-blocking loops.

### 🟢 4x4 Matrix Keypad BSP Driver (`keypad`)
- [x] **Layered Hardware Abstraction:** Built cleanly on top of `stm32f411xx_gpio_driver` without touching raw registers in user code.
- [x] **Active Column Scanning:** Sequentially driving active column HIGH (Push-Pull) with internal Pull-Down row sampling.
- [x] **Signal Settling Delay:** Volatile NOP delay to ensure capacitance stabilization and reliable logic thresholds before reading inputs.
- [x] **Non-Blocking Debounce FSM:** 3-state Finite State Machine (`IDLE` ➔ `DEBOUNCE` ➔ `PRESSED`) filtering mechanical contact bounce using SysTick timestamps.
- [x] **Single-Press Semantics:** Key release detection ensuring a held key is reported exactly once without flooding.

---

## 🗺️ Roadmap (Upcoming Drivers)

The repository will expand to include bare-metal drivers for key serial communication protocols:

- [ ] **SPI (Serial Peripheral Interface):**
  - Master & Slave operational modes
  - Full-duplex and Simplex data transmission
  - Polling and Interrupt-driven transfer modes
- [ ] **I2C (Inter-Integrated Circuit):**
  - Standard (100 kHz) and Fast (400 kHz) mode support
  - Master Transmitter / Receiver sequences with ACK/NACK management
  - Event and Error interrupt handling
- [ ] **UART / USART (Universal Synchronous/Asynchronous Receiver Transmitter):**
  - Dynamic baud rate calculation and configuration
  - Asynchronous TX/RX interrupt support and Circular Buffer (Ring Buffer) integration

---

## 📁 Repository Structure

```text
stm32f411ceux_drivers/
├── BSP/                               # Board Support Package (External Modules)
│   ├── Inc/
│   │   └── keypad.h                   # 4x4 Keypad definitions & FSM types
│   └── Src/
│       └── keypad.c                   # Keypad scanning & debounce implementation
├── Core/
│   ├── Inc/
│   │   └── system_stm32f4xx.h         # System clock header
│   └── Src/
│       ├── main.c                     # Application entry point & driver test code
│       └── system_stm32f4xx.c         # Clock tree initialization & SystemCoreClock
├── Drivers/
│   ├── CMSIS/                         # ARM Cortex-M4 core definitions & headers
│   ├── Inc/
│   │   ├── stm32f411xx_hal.h          # Peripheral base addresses & clock macros
│   │   ├── stm32f411xx_gpio_driver.h  # GPIO driver API declarations & data structures
│   │   └── stm32f411xx_systick_driver.h # SysTick timer API declarations
│   └── Src/
│       ├── stm32f411xx_gpio_driver.c  # GPIO driver implementation & Doxygen docs
│       └── stm32f411xx_systick_driver.c # SysTick timer implementation & interrupt handler
├── cmake/                             # CMake toolchain configuration
├── CMakeLists.txt                     # Project build rules
├── CMakePresets.json                  # Presets for Debug and Release builds
└── STM32F411xx_FLASH.ld               # Flash linker script for STM32F411CEU6
```

---

## ⚙️ Building the Project

Ensure you have `arm-none-eabi-gcc`, `cmake`, and `ninja` installed on your system.

```bash
# 1. Configure the project using the Debug preset
cmake --preset Debug

# 2. Compile the executable
cmake --build build/Debug
```

The compiled output (`.elf`, `.bin`, `.hex`) will be located in the `build/Debug/` directory.
