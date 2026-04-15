#include <gtest/gtest.h>
#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"

struct JumpTestCase {
    uint8_t opcode;        
    CPU::AddressingMode mode;
    uint16_t baseAddr;    
    uint16_t expectedPC;  
    const char* name;
};

class JumpInstructions : public ::testing::TestWithParam<JumpTestCase> {
protected:
    Bus bus;
    CPU cpu{bus};
};

TEST_P(JumpInstructions, Execute) {
    auto test = GetParam();
    cpu.reset();

    if (test.mode == CPU::AddressingMode::Absolute) {

        bus.write(0x0000, static_cast<uint8_t>(test.opcode));
        bus.write(0x0001, static_cast<uint8_t>(test.baseAddr & 0xFF));
        bus.write(0x0002, static_cast<uint8_t>((test.baseAddr >> 8) & 0xFF));
    } else if (test.mode == CPU::AddressingMode::Indirect) {

        bus.write(0x0000, static_cast<uint8_t>(test.opcode));
        bus.write(0x0001, static_cast<uint8_t>(test.baseAddr & 0xFF));   
        bus.write(0x0002, static_cast<uint8_t>((test.baseAddr >> 8) & 0xFF)); 

        uint16_t ptr = test.baseAddr; 
        uint16_t target = test.expectedPC;

        uint16_t highAddr = ((ptr & 0x00FF) == 0xFF) ? (ptr & 0xFF00) : ptr + 1;

        bus.write(ptr, static_cast<uint8_t>(target & 0xFF));           
        bus.write(highAddr, static_cast<uint8_t>((target >> 8) & 0xFF)); 
        }

    cpu.setPC(0x0000);
    cpu.executeInstruction();
    EXPECT_EQ(cpu.getPC(), test.expectedPC);
}

INSTANTIATE_TEST_SUITE_P(
    JumpTests,
    JumpInstructions,
    ::testing::Values(
        JumpTestCase{Ops::JMP_ABS, CPU::AddressingMode::Absolute, 0x1234, 0x1234, "JMP_ABS_basic"},
        JumpTestCase{Ops::JMP_IND, CPU::AddressingMode::Indirect, 0x0200, 0x0345, "JMP_IND_basic"},
        JumpTestCase{Ops::JMP_IND, CPU::AddressingMode::Indirect, 0x02FF, 0x0400, "JMP_IND_bug"},
        JumpTestCase{Ops::JSR, CPU::AddressingMode::Absolute, 0x0500, 0x0500, "JSR_ABS_basic"}
    ),
    [](const ::testing::TestParamInfo<JumpTestCase>& info) {
        return std::string(info.param.name);
    }
);
