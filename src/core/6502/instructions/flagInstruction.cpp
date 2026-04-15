#include "../cpu.h"
#include "../flags.h"

void CPU::opCLC (AddressingMode mode) { registers.P.clear(Flags::CARRY); }
void CPU::opCLD(AddressingMode mode)  { registers.P.clear(Flags::DECIMAL_MODE); }
void CPU::opCLI (AddressingMode mode)  { registers.P.clear(Flags::INTERRUPT_DISABLE); }
void CPU::opCLV (AddressingMode mode)  { registers.P.clear(Flags::OVERFLOW); }
void CPU::opSEC (AddressingMode mode)  { registers.P.set(Flags::CARRY); }
void CPU::opSED (AddressingMode mode)  { registers.P.set(Flags::DECIMAL_MODE); }
void CPU::opSEI (AddressingMode mode)  { registers.P.set(Flags::INTERRUPT_DISABLE); }