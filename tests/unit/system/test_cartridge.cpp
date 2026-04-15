#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <cstdio> /
#include "../../src/bus/bus.h"       
#include "../../src/system/cartridge/cartridge.h"


void createTestROM(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    
    char header[] = {
        'N', 'E', 'S', 0x1A, 
        0x01, 
        0x01, 
        0x00, 
        0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
    };
    file.write(header, 16);


    std::vector<char> prgData(16384, 0xAA);

    prgData[0] = 0x11;
    prgData[16383] = 0x99;
    file.write(prgData.data(), prgData.size());

    std::vector<char> chrData(8192, 0xBB);
    file.write(chrData.data(), chrData.size());
    
    file.close();
}

TEST(CartridgeTests, CorrectlyLoadsHeaderAndData) {
    std::string filename = "test_rom.nes";
    createTestROM(filename);

    auto cart = std::make_shared<Cartridge>(filename);
    
    Bus bus;
    bus.insertCartridge(cart);
    EXPECT_EQ(bus.read(0x8000), 0x11);
    EXPECT_EQ(bus.read(0xBFFF), 0x99);
    EXPECT_EQ(bus.read(0xC000), 0x11);
    
  
    EXPECT_EQ(bus.read(0x8050), 0xAA);

    std::remove(filename.c_str());
}

TEST(CartridgeTests, ReadOnlyBehavior) {

    std::string filename = "test_rom_rw.nes";
    createTestROM(filename);
    Bus bus;
    auto cart = std::make_shared<Cartridge>(filename);
    bus.insertCartridge(cart);

    bus.write(0x8000, 0xFE);
    EXPECT_EQ(bus.read(0x8000), 0xFE); 
    
    std::remove(filename.c_str());
}
