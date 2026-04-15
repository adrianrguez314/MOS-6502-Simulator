#include "../cpu.h"
#include "../flags.h"

void CPU::opPHA(AddressingMode mode) {
    pushStack(registers.A);  
}

void CPU::opPLA(AddressingMode mode) {
    registers.A = pullStack(); 
    registers.P.updateZN(registers.A); 
}

void CPU::opPHP(AddressingMode mode) {
    uint8_t status = registers.P.raw() | (1 << Flags::BREAK_COMMAND) | (1 << Flags::UNUSED);
    pushStack(status);
}


void CPU::opPLP(AddressingMode mode) {
    uint8_t status = pullStack();

    status &= ~(1 << Flags::BREAK_COMMAND);
    status |= (1 << Flags::UNUSED);

    registers.P.raw(status);
}

void CPU::opTXS (AddressingMode mode) {
    registers.SP = registers.X;
}

void CPU::opTSX (AddressingMode mode) {
    registers.X = registers.SP;
    registers.P.updateZN(registers.X);
}