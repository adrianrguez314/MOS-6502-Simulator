#include <iostream>
#include <iomanip>

#include "cpu.h"
#include "opcodes.h"


CPU::CPU(Bus& bus) : bus(bus) {
    initOpcodeTable();
    reset();
    std::cout << "CPU initialized.\n";
}

CPU::~CPU () {
    std::cout << "CPU destroyed.\n";
}

void CPU::reset() {
    registers.A = 0;
    registers.X = 0;
    registers.Y = 0;
    registers.PC = 0;
    registers.SP = STACK_RESET_POINTER;
    registers.P.raw(STATUS_RESET_VALUE);
}

void CPU::pushStack (uint8_t value) {
    bus.write(STACK_BASE + registers.SP, value);
    registers.SP--;
}

uint8_t CPU::pullStack() {
    registers.SP++;  
    return bus.read(STACK_BASE + registers.SP);
}

int CPU::executeInstruction() {
    extra_cycles = 0;  
    page_crossed = false;

    uint8_t opcode = bus.read(registers.PC);
    registers.PC++;
    uint16_t pc_status = registers.PC;
    
    const Instruction& instr = OPCODE_TABLE[opcode];
    (this->*instr.handler)(instr.mode); 

    return instr.cycles + extra_cycles;
}

void CPU::run(int cycles_to_run) {
    while (cycles_to_run > 0) {
        if (cycles_remaining <= 0) {
            if (debug_enabled) trace();
            int cycles_consumed = executeInstruction();
            cycles_remaining = cycles_consumed;
        }

        cycles_remaining--;
        cycles_to_run--;
        total_cycles++;

    }
}

void CPU::branchRelative(bool condition) {

    int8_t offset = static_cast<int8_t>(bus.read(registers.PC)); 
    registers.PC++; 
    
    if (condition) {
        addCycles(1); 
        uint16_t oldPC = registers.PC; 
        uint16_t newPC = oldPC + offset;
        
        if ((oldPC & 0xFF00) != (newPC & 0xFF00)) {
            addCycles(1);
        }

        registers.PC = newPC;
    } 
}

uint8_t CPU::getRegister(char registerName) const {
    switch (registerName) {
        case 'A':
            return registers.A;
        case 'X':
            return registers.X;
        case 'Y': 
            return registers.Y;
        case 'S':
            return registers.SP;
        default:
            throw std:: invalid_argument("Invalid CPU register");
    }
}

void CPU::trace(std::ostream& os) {
    uint8_t debugOpcode = bus.read(registers.PC);
    
    std::cout << std::hex << std::uppercase << std::setfill('0');

    std::cout << std::setw(4) << static_cast<int>(registers.PC) << "  "
              << std::setw(2) << static_cast<int>(debugOpcode) << "        "
              << "A:"  << std::setw(2) << static_cast<int>(registers.A) << " "
              << "X:"  << std::setw(2) << static_cast<int>(registers.X) << " "
              << "Y:"  << std::setw(2) << static_cast<int>(registers.Y) << " "
              << "SP:"  << std::setw(2) << static_cast<int>(registers.SP) << " "
              << "P:" << std::setw(2) << static_cast<int>(registers.P.raw()) << " "
              << std::dec << "CYC:" << total_cycles 
              << std::endl;
}

