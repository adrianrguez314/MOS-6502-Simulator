#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"
#include "../../../../../src/core/6502/flags.h"


TEST(ArithmeticInstructions, INC_DEC_Memory) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::INC_ZP));
    bus.write(0x0001, 0x10);
    bus.write(0x0010, 0x05);

    cpu.executeInstruction();
    EXPECT_EQ(bus.read(0x0010), 0x06);

    bus.write(0x0002, static_cast<uint8_t>(Ops::DEC_ZP));
    bus.write(0x0003, 0x10);

    cpu.executeInstruction();
    EXPECT_EQ(bus.read(0x0010), 0x05);
}

TEST(ArithmeticInstructions, INX_DEX) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::INX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x11);

    bus.write(0x0003, static_cast<uint8_t>(Ops::DEX));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
}

TEST(ArithmeticInstructions, INY_DEY) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0001, 0x20);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::INY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x21);

    bus.write(0x0003, static_cast<uint8_t>(Ops::DEY));
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x20);
}

TEST(ArithmeticInstructions, ADC_Immediate) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x10);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::ADC_IMM));
    bus.write(0x0003, 0x05);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x15);
}

TEST(ArithmeticInstructions, ADC_WrapAround) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0xFF);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::ADC_IMM));
    bus.write(0x0003, 0x02);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x01);
}

TEST(ArithmeticInstructions, SBC_Immediate) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::CARRY); 

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x10);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::SBC_IMM));
    bus.write(0x0003, 0x03);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0x0D);
}

TEST(ArithmeticInstructions, SBC_WrapAround) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::CARRY);  

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x00);
    cpu.executeInstruction();

    bus.write(0x0002, static_cast<uint8_t>(Ops::SBC_IMM));
    bus.write(0x0003, 0x01);
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getRegister('A'), 0xFF);
}



