#include "../cpu.h"
#include "../flags.h"

void CPU::opASL(AddressingMode mode) {
    uint16_t addr = (mode != AddressingMode::Accumulator) ? getAddress(mode) : 0;
    uint8_t* target = (mode == AddressingMode::Accumulator) ? &registers.A : nullptr;
    uint8_t value = target ? *target : bus.read(addr);

    (value & 0x80) ? registers.P.set(Flags::CARRY) : registers.P.clear(Flags::CARRY);
    value <<= 1;

    if (target) *target = value;
    else bus.write(addr, value);

    registers.P.updateZN(value);
}

void CPU::opLSR(AddressingMode mode) {
    uint16_t addr = (mode != AddressingMode::Accumulator) ? getAddress(mode) : 0;
    uint8_t* target = (mode == AddressingMode::Accumulator) ? &registers.A : nullptr;
    uint8_t value = target ? *target : bus.read(addr);

    (value & 0x01) ? registers.P.set(Flags::CARRY) : registers.P.clear(Flags::CARRY);
    value >>= 1;

    if (target) *target = value;
    else bus.write(addr, value);

    registers.P.updateZN(value);
}

void CPU::opROL(AddressingMode mode) {
    uint16_t addr = (mode != AddressingMode::Accumulator) ? getAddress(mode) : 0;
    uint8_t* target = (mode == AddressingMode::Accumulator) ? &registers.A : nullptr;
    uint8_t value = target ? *target : bus.read(addr);
    uint8_t oldCarry = registers.P.isSet(Flags::CARRY) ? 1 : 0;

    (value & 0x80) ? registers.P.set(Flags::CARRY) : registers.P.clear(Flags::CARRY);
    value = (value << 1) | oldCarry;

    if (target) *target = value;
    else bus.write(addr, value);

    registers.P.updateZN(value);
}

void CPU::opROR(AddressingMode mode) {
    uint16_t addr = (mode != AddressingMode::Accumulator) ? getAddress(mode) : 0;
    uint8_t* target = (mode == AddressingMode::Accumulator) ? &registers.A : nullptr;
    uint8_t value = target ? *target : bus.read(addr);
    uint8_t oldCarry = registers.P.isSet(Flags::CARRY) ? 0x80 : 0x00;

    (value & 0x01) ? registers.P.set(Flags::CARRY) : registers.P.clear(Flags::CARRY);
    value = (value >> 1) | oldCarry;

    if (target) *target = value;
    else bus.write(addr, value);
    
    registers.P.updateZN(value);
}