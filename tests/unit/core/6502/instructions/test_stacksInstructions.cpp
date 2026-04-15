#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/flags.h"
#include "../../../../../src/core/6502/opcodes.h"

class StackRegisterInstructions : public ::testing::Test {
protected:
    Bus bus;
    CPU cpu{bus};

    void SetUp() override {
        cpu.reset();
    }

    uint8_t topStack() {
        return bus.read(0x0100 + cpu.getRegister('S') + 1);
    }
};

TEST_F(StackRegisterInstructions, PHA_PLA) {
    cpu.setA(0x42);
    cpu.opPHA(CPU::AddressingMode::Immediate);

    EXPECT_EQ(topStack(), 0x42);
    EXPECT_EQ(cpu.getRegister('S'), 0xFC);

    cpu.setA(0x00);
    cpu.opPLA(CPU::AddressingMode::Immediate);

    EXPECT_EQ(cpu.getRegister('A'), 0x42); 
    EXPECT_EQ(cpu.getRegister('S'), 0xFD);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));
}

TEST_F(StackRegisterInstructions, PHP_PLP) {
    cpu.getFlags().raw(0b10101010); 
    cpu.opPHP(CPU::AddressingMode::Immediate);

    uint8_t expectedStatus = 0b10101010 | (1 << Flags::BREAK_COMMAND) | (1 << Flags::UNUSED);
    EXPECT_EQ(topStack(), expectedStatus);
    EXPECT_EQ(cpu.getRegister('S'), 0xFC);

    cpu.getFlags().raw(0);
    cpu.opPLP(CPU::AddressingMode::Immediate);
    EXPECT_EQ(cpu.getFlags().raw(), 0xAA);
    EXPECT_EQ(cpu.getRegister('S'), 0xFD);
}

TEST_F(StackRegisterInstructions, TXS_TSX) {
    cpu.setX(0x77);
    cpu.opTXS(CPU::AddressingMode::Immediate);
    EXPECT_EQ(cpu.getRegister('S'), 0x77);

    cpu.getFlags().raw(0);
    cpu.opTSX(CPU::AddressingMode::Immediate);
    EXPECT_EQ(cpu.getRegister('X'), 0x77);
    EXPECT_EQ(cpu.getFlags().isSet(Flags::ZERO), false);
    EXPECT_EQ(cpu.getFlags().isSet(Flags::NEGATIVE), false);

    cpu.setSP(0x80);
    cpu.opTSX(CPU::AddressingMode::Immediate);
    EXPECT_EQ(cpu.getRegister('X'), 0x80);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::NEGATIVE)); 
}
