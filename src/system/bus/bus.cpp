#include "bus.h"

Bus::Bus() {
    cpuRam.fill(0x00);
    // ppu = std::make_shared<PPU>();
}

Bus::~Bus() {}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge) {
    this->cart = cartridge;
    // this->ppu->connectCartridge(cartridge); // PPU conector (future)
}

uint8_t Bus::read(uint16_t addr, bool bReadOnly) {
    uint8_t data = 0x00;
    
    if (cart && cart->cpuRead(addr, data)) { }
    else if (addr >= 0x0000 && addr <= 0x1FFF) {
        data = cpuRam[addr & 0x07FF];
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        //data = ppu->cpuRead(addr & 0x0007, bReadOnly);
    }

    return data;
}

void Bus::write(uint16_t addr, uint8_t value) {
    if (cart && cart->cpuWrite(addr, value)) {
    }
    else if (addr >= 0x0000 && addr <= 0x1FFF) {
        cpuRam[addr & 0x07FF] = value;
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        //ppu->cpuWrite(addr & 0x0007, value);
    }
}

uint16_t Bus::read_u16(uint16_t addr) {
    uint8_t low = this->read(addr);
    uint8_t high = this->read(addr + 1);
    return static_cast<uint16_t>(high) << 8 | low;
}

void Bus::write_u16(uint16_t addr, uint16_t value) {
    uint8_t low = value & 0xFF;
    uint8_t high = value >> 8;
    this->write(addr, low);
    this->write(addr + 1, high);
}