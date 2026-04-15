#include "../cpu.h"
#include "../flags.h"

void CPU::opAND(AddressingMode mode) {
    uint16_t addr = CPU::getAddress(mode);
    uint8_t value = bus.read(addr);

    if (page_crossed) tick(1);

    registers.A &= value;

    registers.P.updateZN(registers.A);
}

void CPU::opORA(AddressingMode mode) {
    uint16_t addr = CPU::getAddress(mode);

    uint8_t value = bus.read(addr);
    
    if (page_crossed) tick(1);
    
    registers.A |= value;

    registers.P.updateZN(registers.A);
}

void CPU::opEOR(AddressingMode mode) {
    uint16_t addr = CPU::getAddress(mode);

    uint8_t value = bus.read(addr);

    if (page_crossed) tick(1);

    registers.A ^= value;

    registers.P.updateZN(registers.A);
}

void CPU::opBIT(AddressingMode mode){
    uint16_t addr = CPU::getAddress(mode);

    uint8_t value = bus.read(addr);

    registers.P.updateBIT(registers.A,value);
}