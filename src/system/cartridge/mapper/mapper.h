#ifndef mapper_H
#define mapper_H

#include <cstdint>

class Mapper {
public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks) : nPRGBanks(prgBanks), nCHRBanks(chrBanks) {}
    virtual ~Mapper() = default;

    virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;

protected:
    uint8_t nPRGBanks = 0; 
    uint8_t nCHRBanks = 0; 
};

#endif // mapper_h