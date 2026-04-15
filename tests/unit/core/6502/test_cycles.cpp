#include <gtest/gtest.h>
#include "../../src/core/6502/cpu.h"
#include "../../src/core/6502/opcodes.h"

void loadProgram(Bus& bus, uint16_t addr, std::initializer_list<uint8_t> instructions) {
    for (auto byte : instructions) {
        bus.write(addr++, byte);
    }
}

bool debugActive = true;

TEST(CPUTiming, LoopExecutionCycles) {
    Bus mem;
    CPU cpu(mem);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setPC(0x0000);

    loadProgram(mem, 0x0000, {
        Ops::LDA_IMM, 0x10,
        Ops::TAX,
        Ops::STA_ABS, 0x20, 0x00 
    });

    cpu.run(8);

    EXPECT_EQ(cpu.getCycles(), 8ULL);
    EXPECT_EQ(cpu.getRegister('A'), 0x10);
    EXPECT_EQ(cpu.getRegister('X'), 0x10);
    EXPECT_TRUE(cpu.isInstructionComplete());
}

TEST(CPUTiming, LoopWithEnums) {
    Bus bus;
    CPU cpu(bus);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setPC(0x0000); 

    loadProgram(bus, 0x0000, {
        Ops::LDX_IMM, 0x03, 
        Ops::DEX,           
        Ops::BNE, 0xFD       
    });

    cpu.run(14);

    EXPECT_EQ(cpu.getCycles(), 14ULL);
    EXPECT_EQ(cpu.getRegister('X'), 0x00);
    EXPECT_TRUE(cpu.isInstructionComplete());
}

TEST(CPUTiming, ArithmeticAndFlagsTiming) {
    Bus bus;
    CPU cpu(bus);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setPC(0x0000);

    loadProgram(bus, 0x0000, {
        Ops::SEC,         
        Ops::SBC_IMM, 0x01  
    });

    cpu.run(4);

    EXPECT_EQ(cpu.getCycles(), 4ULL);
    EXPECT_TRUE(cpu.isInstructionComplete());
}

TEST(CPUTiming, MultiplicationLoop) {
    Bus bus;
    CPU cpu(bus);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setPC(0x0000);

    loadProgram(bus, 0x0000, {
        Ops::LDA_IMM, 0x00,  
        Ops::LDX_IMM, 0x04,  
        Ops::CLC,            
        Ops::ADC_IMM, 0x03,  
        Ops::DEX,           
        Ops::BNE, 0xFA       
    });

    cpu.run(39);

    EXPECT_EQ(cpu.getCycles(), 39ULL);
    EXPECT_EQ(cpu.getRegister('A'), 12); 
    EXPECT_EQ(cpu.getRegister('X'), 0);
    EXPECT_TRUE(cpu.isInstructionComplete());
}

TEST(CPUTiming, MemoryCopyStress) {
    Bus bus;
    CPU cpu(bus);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setPC(0x0000); 


    bus.write(0x0300, 0xDE); 
    bus.write(0x0301, 0xAD); 
    bus.write(0x0302, 0xBE);

    loadProgram(bus, 0x0000, {
        Ops::LDX_IMM, 0x02,    
        Ops::LDA_ABSX, 0x00, 0x03, 
        Ops::STA_ABSX, 0x00, 0x04,
        Ops::DEX,
        Ops::BPL, 0xF7        
    });

    cpu.run(43);

    EXPECT_EQ(bus.read(0x0400), 0xDE);
    EXPECT_EQ(bus.read(0x0401), 0xAD);
    EXPECT_EQ(bus.read(0x0402), 0xBE);
    EXPECT_TRUE(cpu.isInstructionComplete());
}

TEST(CPUTiming, SubroutineStackCheck) {
    Bus bus;
    CPU cpu(bus);
    cpu.setDebugMode(debugActive); 
    cpu.reset();
    cpu.setSP(0xFD); 
    cpu.setPC(0x0000); 

    loadProgram(bus, 0x0000, {
        Ops::JSR, 0x10, 0x00,
        Ops::TAX
    });


    loadProgram(bus, 0x0010, { 
        Ops::LDA_IMM, 0x42, 
        Ops::RTS 
    });

    cpu.run(16);

    EXPECT_EQ(cpu.getCycles(), 16ULL);
    EXPECT_EQ(cpu.getRegister('A'), 0x42);
    EXPECT_EQ(cpu.getRegister('X'), 0x42);
    EXPECT_EQ(cpu.getRegister('S'), 0xFD);
}
