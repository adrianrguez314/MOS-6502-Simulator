#include <gtest/gtest.h>

#include "../../src/cpu/cpu.h"
#include "../../src/cpu/opcodes.h"

class SubroutineInstructions : public ::testing::Test {
protected:
    Bus bus;
    CPU cpu{bus};

    void SetUp() override {
        cpu.reset();
        cpu.setPC(0x8000);
    }

    uint8_t topStack() {
        return bus.read(0x0100 + cpu.getRegister('S') + 1);
    }

    uint8_t stackPeek(uint8_t offset = 0) {
        return bus.read(0x0100 + cpu.getRegister('S') + 1 + offset);
    }
};

TEST_F(SubroutineInstructions, JSR_pushes_return_and_jumps) {
    cpu.setPC(0x0000);
    bus.write(0x0000, static_cast<uint8_t>(Ops::JSR));
    bus.write(0x0001, 0x00);
    bus.write(0x0002, 0x02);

    uint8_t initialSP = cpu.getRegister('S');

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), 0x0200);

    uint16_t returnAddr = 0x0002;
    uint8_t pushedHigh = bus.read(0x0100 + initialSP);
    uint8_t pushedLow  = bus.read(0x0100 + initialSP - 1);

    EXPECT_EQ(pushedHigh, (returnAddr >> 8) & 0xFF); 
    EXPECT_EQ(pushedLow,  returnAddr & 0xFF);        
    EXPECT_EQ(cpu.getRegister('S'), static_cast<uint8_t>(initialSP - 2));
}

TEST_F(SubroutineInstructions, RTS_pulls_return_and_continues) {
    cpu.setPC(0x0200);

    cpu.pushStack(0x00); 
    cpu.pushStack(0x02); 

    bus.write(0x0200, static_cast<uint8_t>(Ops::RTS));

    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), 0x0003);
    EXPECT_EQ(cpu.getRegister('S'), 0xFD);
}

TEST_F(SubroutineInstructions, BRK_pushes_pc_and_status_and_jumps) {
    cpu.setPC(0x0000);
    cpu.getFlags().raw(0b01010101); 

    bus.write(0x0000, static_cast<uint8_t>(Ops::BRK));
    
    uint8_t initialSP = cpu.getRegister('S');

    cpu.executeInstruction();

    uint16_t returnAddr = 0x0002; 
    uint8_t expectedStatus = 0b01010101 | (1 << Flags::BREAK_COMMAND) | (1 << Flags::UNUSED);

    uint8_t pch    = bus.read(0x0100 + initialSP);
    uint8_t pcl    = bus.read(0x0100 + initialSP - 1);    
    uint8_t status = bus.read(0x0100 + initialSP - 2);

    EXPECT_EQ(pcl, returnAddr & 0xFF);
    EXPECT_EQ(pch, (returnAddr >> 8) & 0xFF);
    EXPECT_EQ(status, expectedStatus);
    
    EXPECT_EQ(cpu.getPC(), 0x0000);
    EXPECT_TRUE(cpu.getFlags().isSet(Flags::INTERRUPT_DISABLE));
    EXPECT_EQ(cpu.getRegister('S'), static_cast<uint8_t>(initialSP - 3));
}

TEST_F(SubroutineInstructions, RTI_restores_pc_and_status) {
    uint16_t savedPC = 0x3456;
    uint8_t savedStatus = 0b10101010;

    cpu.pushStack((savedPC >> 8) & 0xFF); 
    cpu.pushStack(savedPC & 0xFF);       
    cpu.pushStack(savedStatus);         

    cpu.opRTI(CPU::AddressingMode::Immediate);
    
    EXPECT_EQ(cpu.getPC(), savedPC);
    
    uint8_t expectedStatusAfterRTI = savedStatus & ~(1 << Flags::BREAK_COMMAND);
    expectedStatusAfterRTI |= (1 << Flags::UNUSED);
    
    EXPECT_EQ(cpu.getFlags().raw(), expectedStatusAfterRTI);
    EXPECT_EQ(cpu.getRegister('S'), 0xFD);
} 