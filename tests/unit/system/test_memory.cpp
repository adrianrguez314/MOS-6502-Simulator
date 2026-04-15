#include <gtest/gtest.h>
#include "../../../../src/system/bus/bus.h"

TEST(Memory, ReadWriteByte) {
    Bus bus;
    bus.write(0x0001, 0x30);
    EXPECT_EQ(bus.read(0x0001), 0x30);
}

TEST(Memory, ReadWriteU16) {
    Bus bus;
    bus.write_u16(0x0002, 0x3535);
    EXPECT_EQ(bus.read_u16(0x0002), 0x3535);
}
