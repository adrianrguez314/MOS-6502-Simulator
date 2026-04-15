#include <iostream>

#include "cpu.h"

uint16_t CPU::getAddress(AddressingMode mode) {
    switch (mode) {
        case AddressingMode::Immediate: {
            uint16_t addr = registers.PC;
            registers.PC++;
            return addr;
        }

        case AddressingMode::ZeroPage: {
            uint16_t addr = static_cast<uint16_t>(bus.read(registers.PC));
            registers.PC++; 
            return addr;
        }
    
        case AddressingMode::ZeroPage_X: {
            uint8_t pos = bus.read(registers.PC);
            registers.PC++; 
            return static_cast<uint16_t>((pos + registers.X) & 0xFF);
        }

        case AddressingMode::ZeroPage_Y: {
            uint8_t pos = bus.read(registers.PC);
            registers.PC++; 
            return static_cast<uint16_t>((pos + registers.Y) & 0xFF);
        }

        case AddressingMode::Absolute: {
            uint16_t addr = bus.read_u16(registers.PC);
            registers.PC += 2; 
            return addr;
        }

        case AddressingMode::Absolute_X: {
            uint16_t base = bus.read_u16(registers.PC);
            uint16_t addr = base + registers.X;
            registers.PC += 2; 

            if ((base & 0xFF00) != (addr & 0xFF00)) {
                page_crossed = true;
            }
            return addr;
        }

        case AddressingMode::Absolute_Y: {
            uint16_t base = bus.read_u16(registers.PC);
            uint16_t addr = base + registers.Y;
            registers.PC += 2; 

            if ((base & 0xFF00) != (addr & 0xFF00)) {
                page_crossed = true;
            }
            return addr;
        }

        case AddressingMode::Indirect: {
            uint16_t ptr = bus.read_u16(registers.PC);
            registers.PC += 2; 

            uint8_t low  = bus.read(ptr);
            uint16_t highAddr = (ptr & 0x00FF) == 0xFF ? (ptr & 0xFF00) : ptr + 1;
            uint8_t high = bus.read(highAddr); 

            return static_cast<uint16_t>(high) << 8 | low;
        }

        case AddressingMode::Indirect_X: {
            uint8_t base = bus.read(registers.PC);
            registers.PC++; 

            uint8_t ptr = (base + registers.X) & 0xFF;  
            uint8_t low  = bus.read(ptr);               
            uint8_t high = bus.read((ptr + 1) & 0xFF);  
            return static_cast<uint16_t>(high) << 8 | low;
        }

        case AddressingMode::Indirect_Y: {
            uint8_t base = bus.read(registers.PC);
            registers.PC++; 

            uint8_t low  = bus.read(base);               
            uint8_t high = bus.read((base + 1) & 0xFF);
            uint16_t ptr = (static_cast<uint16_t>(high) << 8 | low);
            
            uint16_t addr = ptr + registers.Y;
            
            if ((ptr & 0xFF00) != (addr & 0xFF00)) {
                page_crossed = true;
            }
            return addr;
        }

        case AddressingMode::Relative: {
            int8_t offset = (int8_t)bus.read(registers.PC);
            registers.PC++; 
            return (registers.PC) + offset;
        }
        
        default:
            return 0;
    }
}