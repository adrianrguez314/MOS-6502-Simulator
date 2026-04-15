#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"

TEST(ShiftInstructions, ASL_Accumulator_And_Memory) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x80); // 1000 0000
    bus.write(0x0002, static_cast<uint8_t>(Ops::ASL_ACC));
    
    cpu.executeInstruction(); 
    cpu.executeInstruction(); 
    
    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));

    bus.write(0x0003, static_cast<uint8_t>(Ops::ASL_ZP));
    bus.write(0x0004, 0x10);
    bus.write(0x0010, 0x01);
    
    cpu.executeInstruction();
    EXPECT_EQ(bus.read(0x0010), 0x02);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
}

TEST(ShiftInstructions, LSR_Accumulator_And_Memory) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x01);
    bus.write(0x0002, static_cast<uint8_t>(Ops::LSR_ACC));
    
    cpu.executeInstruction();
    cpu.executeInstruction();
    
    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));

    bus.write(0x0003, static_cast<uint8_t>(Ops::LSR_ZP));
    bus.write(0x0004, 0x20);
    bus.write(0x0020, 0x80);
    
    cpu.executeInstruction();
    EXPECT_EQ(bus.read(0x0020), 0x40);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::CARRY));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));
}

TEST(ShiftInstructions, ROL_Accumulator_With_Carry) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::CARRY);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x80);
    bus.write(0x0002, static_cast<uint8_t>(Ops::ROL_ACC));

    cpu.executeInstruction(); 
    cpu.executeInstruction(); 

    EXPECT_EQ(cpu.getRegister('A'), 0x01);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY)); 
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
}

TEST(ShiftInstructions, ROR_Memory_With_Carry) {
    Bus bus;
    CPU cpu(bus);

    cpu.getFlags().set(Flags::CARRY);
    bus.write(0x0000, static_cast<uint8_t>(Ops::ROR_ZP));
    bus.write(0x0001, 0x30);
    bus.write(0x0030, 0x01);

    cpu.executeInstruction();

    EXPECT_EQ(bus.read(0x0030), 0x80);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::CARRY));   
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::NEGATIVE)); 
}
