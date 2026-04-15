#include "../cpu.h"
#include "../flags.h"

void CPU::opADC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);


    uint16_t sum = registers.A + value + (registers.P.isSet(Flags::CARRY) ? 1 : 0);

    registers.P.updateOverflow(registers.A, value, static_cast<uint8_t>(sum));
    registers.P.updateCarry(sum);
    
    registers.A = static_cast<uint8_t>(sum);
    registers.P.updateZN(registers.A);

    if (page_crossed) tick(1);
}

void CPU::opSBC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);

    uint16_t sum = registers.A + static_cast<uint8_t>(~value) + (registers.P.isSet(Flags::CARRY) ? 1 : 0);

    registers.P.updateOverflow(registers.A, static_cast<uint8_t>(~value), static_cast<uint8_t>(sum));
    registers.P.updateCarry(sum);

    registers.A = static_cast<uint8_t>(sum);
    registers.P.updateZN(registers.A);

    if (page_crossed) tick(1);
}

void CPU::opINC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);
    
    uint8_t result = value + 1;
    bus.write(addr, result);

    registers.P.updateZN(result);
}

void CPU::opDEC(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);
    
    uint8_t result = value - 1;
    bus.write(addr, result);

    registers.P.updateZN(result);
}

void CPU::opINX(AddressingMode mode) {
    registers.X++;
    registers.P.updateZN(registers.X);
}

void CPU::opINY(AddressingMode mode) {
    registers.Y++;
    registers.P.updateZN(registers.Y);
}

void CPU::opDEX(AddressingMode mode) {
    registers.X--;
    registers.P.updateZN(registers.X);
}

void CPU::opDEY(AddressingMode mode) {
    registers.Y--;
    registers.P.updateZN(registers.Y);
}