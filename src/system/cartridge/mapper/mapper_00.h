#ifndef mapper_000_h
#define mapper_000_h

#include "mapper.h"

class Mapper_000 : public Mapper {
public:
    Mapper_000(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks) {}

    bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) override {
        if (addr >= 0x8000 && addr <= 0xFFFF) {
            mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
            return true;
        }
        return false;
    }

    bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) override {
        if (addr >= 0x8000 && addr <= 0xFFFF) {
            mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
            return true;
        }
        return false;
    }
};
#endif //mapper_00.h