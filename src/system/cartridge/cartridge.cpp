#include "cartridge.h"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(const std::string& fileName)
{
    struct Header {
        char name[4];
        uint8_t prg_rom_chunks;
        uint8_t chr_rom_chunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prg_ram_size;
        uint8_t tv_system1;
        uint8_t tv_system2;
        char unused[5];
    } header;

    std::ifstream ifs(fileName, std::ios::binary);

    if (!ifs.is_open()) {
        bImageValid = false;
        return;
    }

    ifs.read(reinterpret_cast<char*>(&header), sizeof(Header));

    if (header.name[0] != 'N' ||
        header.name[1] != 'E' ||
        header.name[2] != 'S' ||
        header.name[3] != 0x1A)
    {
        bImageValid = false;
        return;
    }

    nPRGBanks = header.prg_rom_chunks;
    nCHRBanks = header.chr_rom_chunks;

    if (nPRGBanks == 0) {
        bImageValid = false;
        return;
    }

    mapper = (header.mapper2 & 0xF0) | (header.mapper1 >> 4);

    PRGMemory.resize(nPRGBanks * 16384);
    CHRMemory.resize(nCHRBanks * 8192);

    if (header.mapper1 & 0x04)
        ifs.seekg(512, std::ios_base::cur);

    ifs.read(reinterpret_cast<char*>(PRGMemory.data()), PRGMemory.size());

    if (CHRMemory.size() > 0)
        ifs.read(reinterpret_cast<char*>(CHRMemory.data()), CHRMemory.size());

    switch (mapper)
    {
        case 0:
            pMapper = std::make_unique<Mapper_000>(nPRGBanks, nCHRBanks);
            break;

        default:
            std::cout << "[ERROR] Unsupported mapper: " << (int)mapper << std::endl;
            bImageValid = false;
            return;
    }

    bImageValid = true;
}
bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
    uint32_t mapped_addr = 0;

    if (!pMapper)
        return false;

    if (pMapper->cpuMapRead(addr, mapped_addr)) {
        data = PRGMemory[mapped_addr];
        return true;
    }

    return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;

    if (!pMapper)
        return false;

    if (pMapper->cpuMapWrite(addr, mapped_addr)) {
        PRGMemory[mapped_addr] = data;
        return true;
    }

    return false;
}