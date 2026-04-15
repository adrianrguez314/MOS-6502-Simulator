#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

#include "mapper/mapper.h"
#include "mapper/mapper_00.h"

class Cartridge {
public:
    Cartridge(const std::string& fileName);
    ~Cartridge() = default;

    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ImageValid() const { return bImageValid; }

private:
    std::vector<uint8_t> PRGMemory;
    std::vector<uint8_t> CHRMemory;

    uint8_t mapper = 0;
    uint8_t nPRGBanks = 0;
    uint8_t nCHRBanks = 0;

    std::unique_ptr<Mapper> pMapper = nullptr;
    bool bImageValid = false;
};

#endif