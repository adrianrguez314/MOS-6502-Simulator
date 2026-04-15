#include "../cpu.h"
#include "../flags.h"

void CPU::opLDA(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);

    if (page_crossed) tick(1);

    registers.P.updateZN(value);
    registers.A = value;
}

void CPU::opLDX(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);

    if (page_crossed) tick(1);

    registers.P.updateZN(value);
    registers.X = value;


}

void CPU::opLDY(AddressingMode mode) {
    uint16_t addr = getAddress(mode);
    uint8_t value = bus.read(addr);

    if (page_crossed) tick(1);

    registers.P.updateZN(value);
    registers.Y = value;
}