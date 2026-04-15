#include <iostream>
#include <iomanip>

#include "./core/6502/cpu.h"
#include "./system/bus/bus.h"

int main() {
    Bus bus;
    CPU cpu(bus);

    std::string romName = "../../nestest.nes";
    auto cart = std::make_shared<Cartridge>(romName);

    if (cart->ImageValid()) {
        bus.insertCartridge(cart);

        cpu.reset();
        cpu.setPC(0xC000);

        for (int i = 0; i < 5000; i++) {
            std::cout << std::hex << std::uppercase << std::setfill('0')
                      << std::setw(4) << cpu.getPC() << "  "
                      << "A:" << std::setw(2) << static_cast<int>(cpu.getRegister('A')) << " "
                      << "X:" << std::setw(2) << static_cast<int>(cpu.getRegister('X')) << " "
                      << "Y:" << std::setw(2) << static_cast<int>(cpu.getRegister('Y')) << " "
                      << "P:" << std::setw(2) << static_cast<int>(cpu.getFlags().raw()) << " "
                      << "SP:" << std::setw(2) << static_cast<int>(cpu.getRegister('S')) << " "
                      << std::dec << "CYC:" << cpu.getCycles() << "\n";

            cpu.executeInstruction();
        }

    } else {
        std::cout << "[ERROR] Don't load the ROM." << std::endl;
    }
    return 0;
}
