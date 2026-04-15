#include "../cpu.h"
#include "../flags.h"

void CPU::opCMP(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);
    
    if (page_crossed) addCycles(1);
    
    uint8_t result = registers.A - value;

    if (registers.A >= value)
        registers.P.set(Flags::CARRY);
    else
        registers.P.clear(Flags::CARRY);

    registers.P.updateZN(result);
}

void CPU::opCPX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);
    
    if (page_crossed) addCycles(1);
    
    uint8_t result = registers.X - value;

    if (registers.X >= value)
        registers.P.set(Flags::CARRY);
    else
        registers.P.clear(Flags::CARRY);

    registers.P.updateZN(result);
}


void CPU::opCPY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);
    
    if (page_crossed) addCycles(1);
    
    uint8_t result = registers.Y - value;

    if (registers.Y >= value)
        registers.P.set(Flags::CARRY);
    else
        registers.P.clear(Flags::CARRY);

    registers.P.updateZN(result);
}