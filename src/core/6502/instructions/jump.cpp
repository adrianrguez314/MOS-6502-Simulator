#include "../cpu.h"
#include "../flags.h"

void CPU::opJMP(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    registers.PC = addr;

}

void CPU::opJSR(AddressingMode mode) {
    uint16_t target = getAddress(mode);
    uint16_t returnAddr = registers.PC - 1;

    pushStack((returnAddr >> 8) & 0xFF); 
    pushStack(returnAddr & 0xFF);        

    registers.PC = target;
}

void CPU::opRTS(AddressingMode mode) {
    uint8_t low = pullStack();
    uint8_t high = pullStack();

    registers.PC = ((uint16_t)high << 8) | low;
    registers.PC++; 
}

void CPU::opBRK(AddressingMode) {
    registers.PC++; 

    pushStack((registers.PC >> 8) & 0xFF); 
    pushStack(registers.PC & 0xFF);       

    uint8_t status = registers.P.raw() | (1 << Flags::BREAK_COMMAND) | (1 << Flags::UNUSED);

    pushStack(status);
    registers.P.set(Flags::INTERRUPT_DISABLE);

    uint8_t low  = bus.read(0xFFFE);
    uint8_t high = bus.read(0xFFFF);
    registers.PC = ((uint16_t)high << 8) | low;
}

void CPU::opRTI(AddressingMode) {
    uint8_t status = pullStack();
    status &= ~(1 << Flags::BREAK_COMMAND);
    status |=  (1 << Flags::UNUSED);
    registers.P.raw(status);

    uint8_t low  = pullStack();
    uint8_t high = pullStack();

    registers.PC = ((uint16_t)high << 8) | low;
}
