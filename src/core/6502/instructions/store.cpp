#include "../cpu.h"


void CPU::opSTA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    bus.write(addr,registers.A);
} 

void CPU::opSTX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    bus.write(addr,registers.X);
} 

void CPU::opSTY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    bus.write(addr,registers.Y);
} 
