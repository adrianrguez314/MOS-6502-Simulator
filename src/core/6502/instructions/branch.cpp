#include "../cpu.h"
#include "../flags.h"


void CPU::opBPL(AddressingMode mode) {
    branchRelative(!registers.P.isSet(Flags::NEGATIVE));
}

void CPU::opBMI(AddressingMode mode) {
    branchRelative(registers.P.isSet(Flags::NEGATIVE));
}

void CPU::opBVC(AddressingMode mode) {
    branchRelative(!registers.P.isSet(Flags::OVERFLOW));
}

void CPU::opBVS(AddressingMode mode) {
    branchRelative(registers.P.isSet(Flags::OVERFLOW));
}

void CPU::opBCC(AddressingMode mode) {
    branchRelative(!registers.P.isSet(Flags::CARRY));
}

void CPU::opBCS(AddressingMode mode) {
    branchRelative(registers.P.isSet(Flags::CARRY));
}

void CPU::opBNE(AddressingMode mode) {
    branchRelative(!registers.P.isSet(Flags::ZERO));
}

void CPU::opBEQ(AddressingMode mode) {
    branchRelative(registers.P.isSet(Flags::ZERO));
}