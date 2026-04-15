#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"
#include "../../../../../src/core/6502/flags.h"


TEST(LogicalInstructions, BIT_Flags_Behavior) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x00); 
    bus.write(0x0002, static_cast<uint8_t>(Ops::BIT_ZP));
    bus.write(0x0003, 0x10); 
    bus.write(0x0010, 0xC0); 
    
    cpu.executeInstruction(); 
    cpu.executeInstruction(); 

    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::NEGATIVE)); 
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::OVERFLOW)); 


    bus.write(0x0004, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0005, 0xFF);
    bus.write(0x0006, static_cast<uint8_t>(Ops::BIT_ZP));
    bus.write(0x0007, 0x11);
    bus.write(0x0011, 0x01); 

    cpu.executeInstruction(); 
    cpu.executeInstruction(); 

    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO)); 
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE)); 
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::OVERFLOW)); 
}

TEST(LogicalInstructions, AND_ORA_EOR) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x0F);
    bus.write(0x0002, static_cast<uint8_t>(Ops::AND_IMM));
    bus.write(0x0003, 0x11);
    
    cpu.executeInstruction();
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('A'), 0x01);
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::ZERO));
    EXPECT_FALSE(cpu.getFlags().isSet(Flags::NEGATIVE));

    bus.write(0x0004, static_cast<uint8_t>(Ops::ORA_IMM));
    bus.write(0x0005, 0x80);
    
    cpu.executeInstruction(); // ORA
    EXPECT_EQ(cpu.getRegister('A'), 0x81);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::NEGATIVE));

    bus.write(0x0006, static_cast<uint8_t>(Ops::EOR_IMM));
    bus.write(0x0007, 0x81);
    
    cpu.executeInstruction(); // EOR
    EXPECT_EQ(cpu.getRegister('A'), 0x00);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::ZERO));
}
