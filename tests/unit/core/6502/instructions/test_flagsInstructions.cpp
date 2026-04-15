#include <gtest/gtest.h>

#include "../../../../../src/core/6502/cpu.h"
#include "../../../../../src/core/6502/opcodes.h"
#include "../../../../../src/core/6502/flags.h"

// Struct para parametrizar cada caso
struct FlagTestCase {
    uint8_t opcode;
    Flags::Flag flag;
    bool expected;
    const char* name;
};

class FlagsInstructions : public ::testing::TestWithParam<FlagTestCase> {
protected:
    Bus bus;
    CPU cpu{bus};
};

TEST_P(FlagsInstructions, Execute) {
    FlagTestCase test = GetParam();

    cpu.reset();

    if (test.opcode == Ops::CLV) {
        cpu.getFlags().updateOverflow(0x50, 0x50, 0xA0);
    }

    bus.write(0x0000, static_cast<uint8_t>(test.opcode));
    cpu.executeInstruction();

    EXPECT_EQ(cpu.getFlags().isSet(test.flag), test.expected);
}

INSTANTIATE_TEST_SUITE_P(
    FlagsTests,
    FlagsInstructions,
    ::testing::Values(
        FlagTestCase{Ops::SEC, Flags::CARRY, true, "SEC"},
        FlagTestCase{Ops::SED, Flags::DECIMAL_MODE, true, "SED"},
        FlagTestCase{Ops::SEI, Flags::INTERRUPT_DISABLE, true, "SEI"},
        FlagTestCase{Ops::CLC, Flags::CARRY, false, "CLC"},
        FlagTestCase{Ops::CLD, Flags::DECIMAL_MODE, false, "CLD"},
        FlagTestCase{Ops::CLI, Flags::INTERRUPT_DISABLE, false, "CLI"},
        FlagTestCase{Ops::CLV, Flags::OVERFLOW, false, "CLV"}
    ),
    [](const ::testing::TestParamInfo<FlagTestCase>& info) {
        return std::string(info.param.name);
    }
);
