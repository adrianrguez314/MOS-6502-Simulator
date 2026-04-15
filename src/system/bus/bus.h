#ifndef bus_h
#define bus_h

#include <cstdint>
#include <array>
#include <memory>

#include "../cartridge/cartridge.h"

class Bus {
public:
    Bus();
    ~Bus();

    uint8_t read(uint16_t addr, bool bReadOnly = false);
    void write(uint16_t addr, uint8_t value);
    uint16_t read_u16(uint16_t addr);
    void write_u16(uint16_t addr, uint16_t value);

    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    
    void reset();

    std::array<uint8_t, 2048> cpuRam{};
    
    std::shared_ptr<Cartridge> cart;
    //std::shared_ptr<PPU> ppu;
};
#endif
