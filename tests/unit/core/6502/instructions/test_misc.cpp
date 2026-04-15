#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"

TEST(MiscInstructions, NOP_does_nothing_but_advances_PC) {
    Bus bus;
    CPU cpu(bus);

    cpu.setPC(0x0000);
    bus.write(0x0000, static_cast<uint8_t>(Ops::NOP));

    uint8_t initialA = cpu.getRegister('A');
    uint8_t initialX = cpu.getRegister('X');
    uint8_t initialY = cpu.getRegister('Y');
    uint8_t initialSP = cpu.getRegister('S');
    uint8_t initialFlags = cpu.getFlags().raw();

    cpu.executeInstruction();

    EXPECT_EQ(cpu.getPC(), 0x0001);
    EXPECT_EQ(cpu.getRegister('A'), initialA);
    EXPECT_EQ(cpu.getRegister('X'), initialX);
    EXPECT_EQ(cpu.getRegister('Y'), initialY);
    EXPECT_EQ(cpu.getRegister('S'), initialSP);
    EXPECT_EQ(cpu.getFlags().raw(), initialFlags);
}
