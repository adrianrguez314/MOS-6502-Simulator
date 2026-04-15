# MOS 6502 Architecture Core: A Formal Implementation
*(MOS 6502 マイクロプロセッサのサイクルアキュレートなコアシミュレータ)*

---

> **A cycle-accurate, headless software simulation of the MOS 6502 microprocessor architecture, designed strictly for Hardware Verification & Validation (V&V).**

---

## Architecture Overview

The **MOS 6502** is an iconic 8-bit microprocessor that defined an era of computing. This project implements the core logic of the 6502, emphasizing the precise handling of its internal state and memory bus interactions in a completely headless environment.

### The Significance of the 6502
Introduced in 1975, the 6502’s efficient design—utilizing a minimal register set and advanced addressing modes—made it the heart of classic microcomputers and iconic embedded systems (such as the Apple II, Commodore, and early Nintendo hardware). Simulating this processor is a fundamental exercise in **Computer Architecture** and **Silicon Verification**, requiring a deep understanding of:

* **Pipelining**: Execution of instructions across multiple clock cycles.
* **Effective Address Calculation**: Implementing complex modes like *Indirect Indexed* ($(Ind), Y$).
* **State Machine Logic**: Managing the Program Counter ($PC$) and Status Register ($P$) with bit-level precision.

---

## System Specifications

| Component | Specification | Description |
| :--- | :--- | :--- |
| **Data Bus** | 8-bit | Standard 8-bit wide data path for arithmetic and logic. |
| **Address Bus** | 16-bit | Provides a $64$ KB addressable memory space. |
| **Registers** | $A, X, Y, PC, S, P$ | Full implementation of the primary 6502 register set. |
| **RAM** | 2 KB | Internal Work RAM (WRAM) with hardware mirroring logic. |
| **Instruction Set** | 56 Opcodes | Full coverage of official MOS 6502 instructions. |

---

## Technical Stack & Quality Assurance

This implementation is built upon modern industry standards, ensuring the code is as robust as the hardware it emulates.

* **Language Standard**: **C++20/23**. Utiliza características de alto rendimiento como `std::span` para seguridad de memoria y `constexpr` para la generación de tablas en tiempo de compilación.
* **Build System**: **CMake**. Configuración multiplataforma que gestiona dependencias y objetivos de compilación.
* **Testing Framework**: **Google Test (GTest)**. Una rigurosa suite de pruebas unitarias valida cada opcode y modo de direccionamiento frente a patrones de comportamiento de hardware conocidos.
* **Continuous Reporting**: Los resultados de las pruebas se renderizan automáticamente en un informe visual `index.html`, alojado a través de **GitHub Pages** para la verificación de integridad en tiempo real.

---

## Bibliography & Documentation

El desarrollo de este núcleo está estrictamente guiado por los siguientes estándares:

1.  **[Nesdev Wiki](https://www.nesdev.org/)**: Fuente principal para las particularidades del hardware y el comportamiento del bus de los chips derivados del 6502.
2.  **MOS 6502 Microprocessor Manual**: Documentación fundamental para la lógica interna de los registros y el timing.
3.  **[ISO/IEC 14882:2020 (C++20 Standard)](https://en.cppreference.com/w/cpp/20)**: Referencia para los paradigmas modernos de C++ utilizados en el proyecto.
4.  **[Google Test Documentation](https://google.github.io/googletest/)**: Directrices para la implementación de la arquitectura de validación del proyecto.

---

## Build and Validation Instructions

Para asegurar que el entorno esté configurado correctamente, siga el procedimiento formal de compilación:

```bash
# Generate build files
cmake -S . -B build

# Compile the CPU core and Test suite
cmake --build build --config Release

# Execute the GTest validation suite
cd build && ctest --output-on-failure
```