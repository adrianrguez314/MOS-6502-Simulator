#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"


TEST(TransferInstructions, Transfers) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x40);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::TAX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x40);

    bus.write(0x0003, static_cast<uint8_t>(Ops::TAY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x40);

    cpu.reset();
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x80);
    cpu.executeInstruction();
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0003, 0x12);
    cpu.executeInstruction();

    bus.write(0x0004, static_cast<uint8_t>(Ops::TXA));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x80);

    bus.write(0x0005, static_cast<uint8_t>(Ops::TYA));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x12);
}
