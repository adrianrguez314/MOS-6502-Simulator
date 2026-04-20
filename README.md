<div align="center">

# 📟 MOS 6502 Architecture Core
### *A Formal, Cycle-Accurate Implementation in C++*
*(MOS 6502 マイクロプロセッサのサイクルアキュレートなコアシミュレータ)*

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-20%2F23-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/Build-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![GTest](https://img.shields.io/badge/Testing-GoogleTest-8A2BE2?style=for-the-badge&logo=google&logoColor=white)](https://google.github.io/googletest/)

</div>

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

* **Language Standard**: **C++20/23**. Utilizes high-performance features such as `std::span` for memory safety and `constexpr` for compile-time table generation.
* **Build System**: **CMake**. A cross-platform configuration that manages dependencies and compilation targets.
* **Testing Framework**: **Google Test (GTest)**. A rigorous suite of unit tests validates every opcode and addressing mode against known hardware behavioral patterns.
* **Continuous Reporting**: Test results are automatically rendered into a visual `index.html` report, hosted via **GitHub Pages** for real-time integrity verification.

...
* **Continuous Reporting**: Test results are automatically rendered into a visual `index.html` report.

---

### 🔍 Core Execution Trace
To validate pipeline integrity, the core generates detailed, cycle-accurate logs for every instruction execution:

<p align="center">
  <img src="https://i.imgur.com/5YllX7s.png" alt="MOS 6502 Core Execution Trace Preview" width="800">
  <br>
  <em>Figure 2: Real-time trace showing the synchronized state of the instruction and the resulting register state in the terminal.</em>
</p>

---

## Bibliography & Documentation

The development of this core is strictly guided by the following standards and resources:

1.  **[Nesdev Wiki](https://www.nesdev.org/)**: Primary source for hardware quirks, memory mapping, and bus behavior of 6502 derivative chips.
2.  **MOS 6502 Microprocessor Manual**: Foundational documentation for internal register logic and timing.
3.  **[ISO/IEC 14882:2020 (C++20 Standard)](https://en.cppreference.com/w/cpp/20)**: Reference for the modern C++ paradigms utilized in the project.
4.  **[Google Test Documentation](https://google.github.io/googletest/)**: Guidelines for the implementation of the project's validation architecture.

---

## Build and Validation Instructions

To ensure the environment is correctly configured, follow the formal build procedure:

```bash
# Generate build files
cmake -S . -B build

# Compile the CPU core and Test suite
cmake --build build --config Release

# Execute the GTest validation suite
cd build && ctest --output-on-failure
```
