#include <gtest/gtest.h>
#include "../../src/core/6502/cpu.h"
#include "../../src/core/6502/flags.h"

TEST(Flags, SetClearCarry) {
    Flags P;

    P.set(Flags::CARRY);
    EXPECT_TRUE(P.isSet(Flags::CARRY));

    P.clear(Flags::CARRY);
    EXPECT_FALSE(P.isSet(Flags::CARRY));
}

TEST(Flags, ZeroNegativeFlags) {
    Flags P;

    P.updateZN(0x00);
    EXPECT_TRUE(P.isSet(Flags::ZERO));
    EXPECT_FALSE(P.isSet(Flags::NEGATIVE));

    P.updateZN(0x80);
    EXPECT_FALSE(P.isSet(Flags::ZERO));
    EXPECT_TRUE(P.isSet(Flags::NEGATIVE));
}

TEST(Flags, OverflowFlag) {
    Flags P;

    P.updateOverflow(0x50, 0x50, 0xA0);
    EXPECT_TRUE(P.isSet(Flags::OVERFLOW));

    P.updateOverflow(0x10, 0x10, 0x20);
    EXPECT_FALSE(P.isSet(Flags::OVERFLOW));
}
