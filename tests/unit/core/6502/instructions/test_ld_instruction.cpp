#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"
#include "../../../../../src/core/6502/flags.h"

TEST(LDInstructions, Immediate) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_IMM));
    bus.write(0x0001, 0x42);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x42); 

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x10);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0001, 0x55);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x55);
}

TEST(LDInstructions, ZeroPage) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0010, 0x65);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_ZP));
    bus.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x65);

    bus.write(0x0010, 0x77);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_ZP));
    bus.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x77);

    bus.write(0x0010, 0x88);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_ZP));
    bus.write(0x0001, 0x10);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x88);
}

TEST(LDInstructions, ZeroPageIndexed) {
    Bus bus;
    CPU cpu(bus);

    
    bus.write(0x0090, 0x42);  
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10);
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDA_ZPX));
    bus.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('A'), 0x42);

    cpu.reset();
    bus.write(0x0090, 0x42);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0001, 0x10);
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDX_ZPY));
    bus.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x42);

    cpu.reset();
    bus.write(0x0090, 0x42);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10);
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDY_ZPX));
    bus.write(0x0003, 0x80);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x42);
}


TEST(LDInstructions, Absolute) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x1255, 0x88);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDA_ABS));
    bus.write_u16(0x0001, 0x1255);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('A'), 0x88);

    bus.write(0x1300, 0x77);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_ABS));
    bus.write_u16(0x0001, 0x1300);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('X'), 0x77);

    bus.write(0x1400, 0x66);
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_ABS));
    bus.write_u16(0x0001, 0x1400);
    cpu.reset();
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x66);
}

TEST(LDInstructions, AbsoluteIndexed) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0230, 0x55); 
    
    cpu.setPC(0x0000); 
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10); 
    
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDA_ABSX));
    bus.write_u16(0x0003, 0x0220); 
    
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('A'), 0x55);


    cpu.setPC(0x0000); 
    
    bus.write(0x0230, 0x66); 
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0001, 0x10);

    bus.write(0x0002, static_cast<uint8_t>(Ops::LDX_ABSY));
    bus.write_u16(0x0003, 0x0220); 
    
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getRegister('Y'), 0x10);
    
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x66);


    cpu.setPC(0x0000);
    
    bus.write(0x0230, 0x77); 
    
    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x10); 
    
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDY_ABSX));
    bus.write_u16(0x0003, 0x0220); 
    
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    cpu.executeInstruction(); 
    EXPECT_EQ(cpu.getRegister('Y'), 0x77);
}

TEST(LDInstructions, IndirectX) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDX_IMM));
    bus.write(0x0001, 0x04);
    
    bus.write(0x0002, static_cast<uint8_t>(Ops::LDA_INX));
    bus.write(0x0003, 0x02); 
    bus.write(0x06, 0x10); 
    bus.write(0x07, 0x02); 


    bus.write(0x0210, 0x42); 

    cpu.setPC(0x0000);
    cpu.executeInstruction(); 
    cpu.executeInstruction(); 
    
    EXPECT_EQ(cpu.getRegister('A'), 0x42);
}

TEST(LDInstructions, IndirectY) {
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, static_cast<uint8_t>(Ops::LDY_IMM));
    bus.write(0x0001, 0x05); 

    bus.write(0x0002, static_cast<uint8_t>(Ops::LDA_INY));
    bus.write(0x0003, 0x10); 

    bus.write(0x10, 0x20); 
    bus.write(0x11, 0x03); 

    bus.write(0x0325, 0x99);

    cpu.setPC(0x0000);
    cpu.executeInstruction(); 
    
    cpu.executeInstruction(); 
    
    EXPECT_EQ(cpu.getRegister('A'), 0x99);
}
