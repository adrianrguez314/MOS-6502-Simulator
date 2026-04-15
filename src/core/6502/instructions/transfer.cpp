#include "../cpu.h"
#include "../flags.h"

void CPU::opTAX (AddressingMode mode) {
    registers.X = registers.A;
    registers.P.updateZN(registers.X);
}

void CPU::opTAY(AddressingMode mode) {
    registers.Y = registers.A;
    registers.P.updateZN(registers.Y);
}

void CPU::opTXA (AddressingMode mode) {
    registers.A = registers.X;
    registers.P.updateZN(registers.A);
}

void CPU::opTYA (AddressingMode mode) {
    registers.A = registers.Y;
    registers.P.updateZN(registers.A);
}

