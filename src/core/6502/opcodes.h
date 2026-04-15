#ifndef OPCODES_H
#define OPCODES_H

#include <cstdint>
#include <algorithm>
#include "cpu.h" 

namespace Ops {
    constexpr uint8_t NOP = 0xEA;

    constexpr uint8_t LDA_IMM = 0xA9, LDA_ZP = 0xA5, LDA_ZPX = 0xB5, LDA_ABS = 0xAD, LDA_ABSX = 0xBD, LDA_ABSY = 0xB9, LDA_INX = 0xA1, LDA_INY = 0xB1;
    constexpr uint8_t LDX_IMM = 0xA2, LDX_ZP = 0xA6, LDX_ZPY = 0xB6, LDX_ABS = 0xAE, LDX_ABSY = 0xBE;
    constexpr uint8_t LDY_IMM = 0xA0, LDY_ZP = 0xA4, LDY_ZPX = 0xB4, LDY_ABS = 0xAC, LDY_ABSX = 0xBC;

    constexpr uint8_t STA_ZP = 0x85, STA_ZPX = 0x95, STA_ABS = 0x8D, STA_ABSX = 0x9D, STA_ABSY = 0x99, STA_INX = 0x81, STA_INY = 0x91;
    constexpr uint8_t STX_ZP = 0x86, STX_ZPY = 0x96, STX_ABS = 0x8E;
    constexpr uint8_t STY_ZP = 0x84, STY_ZPX = 0x94, STY_ABS = 0x8C;

    constexpr uint8_t TAX = 0xAA, TAY = 0xA8, TXA = 0x8A, TYA = 0x98;
    constexpr uint8_t TSX = 0xBA, TXS = 0x9A;

    constexpr uint8_t ADC_IMM = 0x69, ADC_ZP = 0x65, ADC_ZPX = 0x75, ADC_ABS = 0x6D, ADC_ABSX = 0x7D, ADC_ABSY = 0x79, ADC_INX = 0x61, ADC_INY = 0x71;
    constexpr uint8_t SBC_IMM = 0xE9, SBC_ZP = 0xE5, SBC_ZPX = 0xF5, SBC_ABS = 0xED, SBC_ABSX = 0xFD, SBC_ABSY = 0xF9, SBC_INX = 0xE1, SBC_INY = 0xF1;

    constexpr uint8_t INC_ZP = 0xE6, INC_ZPX = 0xF6, INC_ABS = 0xEE, INC_ABSX = 0xFE;
    constexpr uint8_t DEC_ZP = 0xC6, DEC_ZPX = 0xD6, DEC_ABS = 0xCE, DEC_ABSX = 0xDE;
    constexpr uint8_t INX = 0xE8, DEX = 0xCA, INY = 0xC8, DEY = 0x88;

    constexpr uint8_t CMP_IMM = 0xC9, CMP_ZP = 0xC5, CMP_ZPX = 0xD5, CMP_ABS = 0xCD, CMP_ABSX = 0xDD, CMP_ABSY = 0xD9, CMP_INDX = 0xC1, CMP_INDY = 0xD1;
    constexpr uint8_t CPX_IMM = 0xE0, CPX_ZP = 0xE4, CPX_ABS = 0xEC;
    constexpr uint8_t CPY_IMM = 0xC0, CPY_ZP = 0xC4, CPY_ABS = 0xCC;

    constexpr uint8_t ASL_ACC = 0x0A, ASL_ZP = 0x06, ASL_ZPX = 0x16, ASL_ABS = 0x0E, ASL_ABSX = 0x1E;
    constexpr uint8_t LSR_ACC = 0x4A, LSR_ZP = 0x46, LSR_ZPX = 0x56, LSR_ABS = 0x4E, LSR_ABSX = 0x5E;
    constexpr uint8_t ROL_ACC = 0x2A, ROL_ZP = 0x26, ROL_ZPX = 0x36, ROL_ABS = 0x2E, ROL_ABSX = 0x3E;
    constexpr uint8_t ROR_ACC = 0x6A, ROR_ZP = 0x66, ROR_ZPX = 0x76, ROR_ABS = 0x6E, ROR_ABSX = 0x7E;
    
    constexpr uint8_t AND_IMM = 0x29, AND_ZP = 0x25, AND_ZPX = 0x35, AND_ABS = 0x2D, AND_ABSX = 0x3D, AND_ABSY = 0x39, AND_INX = 0x21, AND_INY = 0x31;
    constexpr uint8_t ORA_IMM = 0x09, ORA_ZP = 0x05, ORA_ZPX = 0x15, ORA_ABS = 0x0D, ORA_ABSX = 0x1D, ORA_ABSY = 0x19, ORA_INX = 0x01, ORA_INY = 0x11;
    constexpr uint8_t EOR_IMM = 0x49, EOR_ZP = 0x45, EOR_ZPX = 0x55, EOR_ABS = 0x4D, EOR_ABSX = 0x5D, EOR_ABSY = 0x59, EOR_INX = 0x41, EOR_INY = 0x51;
    constexpr uint8_t BIT_ZP  = 0x24, BIT_ABS = 0x2C;

    constexpr uint8_t JMP_ABS = 0x4C, JMP_IND = 0x6C;
    constexpr uint8_t JSR = 0x20, RTS = 0x60;
    constexpr uint8_t BRK = 0x00, RTI = 0x40;
    
    constexpr uint8_t PHA = 0x48, PLA = 0x68, PHP = 0x08, PLP = 0x28;
    
    constexpr uint8_t CLC = 0x18, CLD = 0xD8, CLI = 0x58, CLV = 0xB8, SEC = 0x38, SED = 0xF8, SEI = 0x78;

    constexpr uint8_t BPL = 0x10, BMI = 0x30, BVC = 0x50, BVS = 0x70, BCC = 0x90, BCS = 0xB0, BNE = 0xD0, BEQ = 0xF0;
}

struct Instruction {
    CPU::AddressingMode mode;
    uint8_t len;
    uint8_t cycles;
    void (CPU::*handler)(CPU::AddressingMode);
};

static Instruction OPCODE_TABLE[256];

inline void initOpcodeTable() {
    using AM = CPU::AddressingMode;

    Instruction nopInstr = { AM::Not_addressing, 1, 2, &CPU::opNOP };
    std::fill(std::begin(OPCODE_TABLE), std::end(OPCODE_TABLE), nopInstr);

    auto reg = [](uint8_t op, AM mode, uint8_t len, uint8_t cyc, void (CPU::*func)(AM)) {
        OPCODE_TABLE[op] = { mode, len, cyc, func };
    };

    // --- Load / Store ---
    reg(Ops::LDA_IMM,  AM::Immediate,   2, 2, &CPU::opLDA);
    reg(Ops::LDA_ZP,   AM::ZeroPage,    2, 3, &CPU::opLDA);
    reg(Ops::LDA_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opLDA);
    reg(Ops::LDA_ABS,  AM::Absolute,    3, 4, &CPU::opLDA);
    reg(Ops::LDA_ABSX, AM::Absolute_X,  3, 4, &CPU::opLDA);
    reg(Ops::LDA_ABSY, AM::Absolute_Y,  3, 4, &CPU::opLDA);
    reg(Ops::LDA_INX,  AM::Indirect_X,  2, 6, &CPU::opLDA);
    reg(Ops::LDA_INY,  AM::Indirect_Y,  2, 5, &CPU::opLDA);

    reg(Ops::LDX_IMM,  AM::Immediate,   2, 2, &CPU::opLDX);
    reg(Ops::LDX_ZP,   AM::ZeroPage,    2, 3, &CPU::opLDX);
    reg(Ops::LDX_ZPY,  AM::ZeroPage_Y,  2, 4, &CPU::opLDX);
    reg(Ops::LDX_ABS,  AM::Absolute,    3, 4, &CPU::opLDX);
    reg(Ops::LDX_ABSY, AM::Absolute_Y,  3, 4, &CPU::opLDX);

    reg(Ops::LDY_IMM,  AM::Immediate,   2, 2, &CPU::opLDY);
    reg(Ops::LDY_ZP,   AM::ZeroPage,    2, 3, &CPU::opLDY);
    reg(Ops::LDY_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opLDY);
    reg(Ops::LDY_ABS,  AM::Absolute,    3, 4, &CPU::opLDY);
    reg(Ops::LDY_ABSX, AM::Absolute_X,  3, 4, &CPU::opLDY);

    reg(Ops::STA_ZP,   AM::ZeroPage,    2, 3, &CPU::opSTA);
    reg(Ops::STA_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opSTA);
    reg(Ops::STA_ABS,  AM::Absolute,    3, 4, &CPU::opSTA);
    reg(Ops::STA_ABSX, AM::Absolute_X,  3, 5, &CPU::opSTA); 
    reg(Ops::STA_ABSY, AM::Absolute_Y,  3, 5, &CPU::opSTA);
    reg(Ops::STA_INX,  AM::Indirect_X,  2, 6, &CPU::opSTA);
    reg(Ops::STA_INY,  AM::Indirect_Y,  2, 6, &CPU::opSTA);

    reg(Ops::STX_ZP,   AM::ZeroPage,    2, 3, &CPU::opSTX);
    reg(Ops::STX_ZPY,  AM::ZeroPage_Y,  2, 4, &CPU::opSTX);
    reg(Ops::STX_ABS,  AM::Absolute,    3, 4, &CPU::opSTX);

    reg(Ops::STY_ZP,   AM::ZeroPage,    2, 3, &CPU::opSTY);
    reg(Ops::STY_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opSTY);
    reg(Ops::STY_ABS,  AM::Absolute,    3, 4, &CPU::opSTY);

    // --- Register / Transfer ---
    reg(Ops::TAX, AM::Not_addressing, 1, 2, &CPU::opTAX);
    reg(Ops::TAY, AM::Not_addressing, 1, 2, &CPU::opTAY);
    reg(Ops::TXA, AM::Not_addressing, 1, 2, &CPU::opTXA);
    reg(Ops::TYA, AM::Not_addressing, 1, 2, &CPU::opTYA);
    reg(Ops::TSX, AM::Not_addressing, 1, 2, &CPU::opTSX);
    reg(Ops::TXS, AM::Not_addressing, 1, 2, &CPU::opTXS);

    // --- Arithmetic ---
    reg(Ops::ADC_IMM,  AM::Immediate,   2, 2, &CPU::opADC);
    reg(Ops::ADC_ZP,   AM::ZeroPage,    2, 3, &CPU::opADC);
    reg(Ops::ADC_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opADC);
    reg(Ops::ADC_ABS,  AM::Absolute,    3, 4, &CPU::opADC);
    reg(Ops::ADC_ABSX, AM::Absolute_X,  3, 4, &CPU::opADC);
    reg(Ops::ADC_ABSY, AM::Absolute_Y,  3, 4, &CPU::opADC);
    reg(Ops::ADC_INX,  AM::Indirect_X,  2, 6, &CPU::opADC);
    reg(Ops::ADC_INY,  AM::Indirect_Y,  2, 5, &CPU::opADC);

    reg(Ops::SBC_IMM,  AM::Immediate,   2, 2, &CPU::opSBC);
    reg(Ops::SBC_ZP,   AM::ZeroPage,    2, 3, &CPU::opSBC);
    reg(Ops::SBC_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opSBC);
    reg(Ops::SBC_ABS,  AM::Absolute,    3, 4, &CPU::opSBC);
    reg(Ops::SBC_ABSX, AM::Absolute_X,  3, 4, &CPU::opSBC);
    reg(Ops::SBC_ABSY, AM::Absolute_Y,  3, 4, &CPU::opSBC);
    reg(Ops::SBC_INX,  AM::Indirect_X,  2, 6, &CPU::opSBC);
    reg(Ops::SBC_INY,  AM::Indirect_Y,  2, 5, &CPU::opSBC);

    // --- Inc / Dec ---
    reg(Ops::INC_ZP,   AM::ZeroPage,    2, 5, &CPU::opINC);
    reg(Ops::INC_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opINC);
    reg(Ops::INC_ABS,  AM::Absolute,    3, 6, &CPU::opINC);
    reg(Ops::INC_ABSX, AM::Absolute_X,  3, 7, &CPU::opINC);

    reg(Ops::DEC_ZP,   AM::ZeroPage,    2, 5, &CPU::opDEC);
    reg(Ops::DEC_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opDEC);
    reg(Ops::DEC_ABS,  AM::Absolute,    3, 6, &CPU::opDEC);
    reg(Ops::DEC_ABSX, AM::Absolute_X,  3, 7, &CPU::opDEC);
    
    reg(Ops::INX, AM::Not_addressing, 1, 2, &CPU::opINX);
    reg(Ops::DEX, AM::Not_addressing, 1, 2, &CPU::opDEX);
    reg(Ops::INY, AM::Not_addressing, 1, 2, &CPU::opINY);
    reg(Ops::DEY, AM::Not_addressing, 1, 2, &CPU::opDEY);

    // --- Compare ---
    reg(Ops::CMP_IMM,  AM::Immediate,   2, 2, &CPU::opCMP);
    reg(Ops::CMP_ZP,   AM::ZeroPage,    2, 3, &CPU::opCMP);
    reg(Ops::CMP_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opCMP);
    reg(Ops::CMP_ABS,  AM::Absolute,    3, 4, &CPU::opCMP);
    reg(Ops::CMP_ABSX, AM::Absolute_X,  3, 4, &CPU::opCMP);
    reg(Ops::CMP_ABSY, AM::Absolute_Y,  3, 4, &CPU::opCMP);
    reg(Ops::CMP_INDX, AM::Indirect_X,  2, 6, &CPU::opCMP);
    reg(Ops::CMP_INDY, AM::Indirect_Y,  2, 5, &CPU::opCMP);

    reg(Ops::CPX_IMM, AM::Immediate, 2, 2, &CPU::opCPX);
    reg(Ops::CPX_ZP,  AM::ZeroPage,  2, 3, &CPU::opCPX);
    reg(Ops::CPX_ABS, AM::Absolute,  3, 4, &CPU::opCPX);
    
    reg(Ops::CPY_IMM, AM::Immediate, 2, 2, &CPU::opCPY);
    reg(Ops::CPY_ZP,  AM::ZeroPage,  2, 3, &CPU::opCPY);
    reg(Ops::CPY_ABS, AM::Absolute,  3, 4, &CPU::opCPY);

    // --- Shifts & Logical ---
    reg(Ops::ASL_ACC,  AM::Accumulator, 1, 2, &CPU::opASL);
    reg(Ops::ASL_ZP,   AM::ZeroPage,    2, 5, &CPU::opASL);
    reg(Ops::ASL_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opASL);
    reg(Ops::ASL_ABS,  AM::Absolute,    3, 6, &CPU::opASL);
    reg(Ops::ASL_ABSX, AM::Absolute_X,  3, 7, &CPU::opASL);

    reg(Ops::LSR_ACC,  AM::Accumulator, 1, 2, &CPU::opLSR);
    reg(Ops::LSR_ZP,   AM::ZeroPage,    2, 5, &CPU::opLSR);
    reg(Ops::LSR_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opLSR);
    reg(Ops::LSR_ABS,  AM::Absolute,    3, 6, &CPU::opLSR);
    reg(Ops::LSR_ABSX, AM::Absolute_X,  3, 7, &CPU::opLSR);

    reg(Ops::ROL_ACC,  AM::Accumulator, 1, 2, &CPU::opROL);
    reg(Ops::ROL_ZP,   AM::ZeroPage,    2, 5, &CPU::opROL);
    reg(Ops::ROL_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opROL);
    reg(Ops::ROL_ABS,  AM::Absolute,    3, 6, &CPU::opROL);
    reg(Ops::ROL_ABSX, AM::Absolute_X,  3, 7, &CPU::opROL);

    reg(Ops::ROR_ACC,  AM::Accumulator, 1, 2, &CPU::opROR);
    reg(Ops::ROR_ZP,   AM::ZeroPage,    2, 5, &CPU::opROR);
    reg(Ops::ROR_ZPX,  AM::ZeroPage_X,  2, 6, &CPU::opROR);
    reg(Ops::ROR_ABS,  AM::Absolute,    3, 6, &CPU::opROR);
    reg(Ops::ROR_ABSX, AM::Absolute_X,  3, 7, &CPU::opROR);

    reg(Ops::AND_IMM,  AM::Immediate,   2, 2, &CPU::opAND);
    reg(Ops::AND_ZP,   AM::ZeroPage,    2, 3, &CPU::opAND);
    reg(Ops::AND_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opAND);
    reg(Ops::AND_ABS,  AM::Absolute,    3, 4, &CPU::opAND);
    reg(Ops::AND_ABSX, AM::Absolute_X,  3, 4, &CPU::opAND);
    reg(Ops::AND_ABSY, AM::Absolute_Y,  3, 4, &CPU::opAND);
    reg(Ops::AND_INX,  AM::Indirect_X,  2, 6, &CPU::opAND);
    reg(Ops::AND_INY,  AM::Indirect_Y,  2, 5, &CPU::opAND);

    reg(Ops::ORA_IMM,  AM::Immediate,   2, 2, &CPU::opORA);
    reg(Ops::ORA_ZP,   AM::ZeroPage,    2, 3, &CPU::opORA);
    reg(Ops::ORA_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opORA);
    reg(Ops::ORA_ABS,  AM::Absolute,    3, 4, &CPU::opORA);
    reg(Ops::ORA_ABSX, AM::Absolute_X,  3, 4, &CPU::opORA);
    reg(Ops::ORA_ABSY, AM::Absolute_Y,  3, 4, &CPU::opORA);
    reg(Ops::ORA_INX,  AM::Indirect_X,  2, 6, &CPU::opORA);
    reg(Ops::ORA_INY,  AM::Indirect_Y,  2, 5, &CPU::opORA);

    reg(Ops::EOR_IMM,  AM::Immediate,   2, 2, &CPU::opEOR);
    reg(Ops::EOR_ZP,   AM::ZeroPage,    2, 3, &CPU::opEOR);
    reg(Ops::EOR_ZPX,  AM::ZeroPage_X,  2, 4, &CPU::opEOR);
    reg(Ops::EOR_ABS,  AM::Absolute,    3, 4, &CPU::opEOR);
    reg(Ops::EOR_ABSX, AM::Absolute_X,  3, 4, &CPU::opEOR);
    reg(Ops::EOR_ABSY, AM::Absolute_Y,  3, 4, &CPU::opEOR);
    reg(Ops::EOR_INX,  AM::Indirect_X,  2, 6, &CPU::opEOR);
    reg(Ops::EOR_INY,  AM::Indirect_Y,  2, 5, &CPU::opEOR);

    reg(Ops::BIT_ZP,   AM::ZeroPage,    2, 3, &CPU::opBIT);
    reg(Ops::BIT_ABS,  AM::Absolute,    3, 4, &CPU::opBIT);

    // --- Control Flow & Stack ---
    reg(Ops::JMP_ABS, AM::Absolute, 3, 3, &CPU::opJMP);
    reg(Ops::JMP_IND, AM::Indirect, 3, 5, &CPU::opJMP);
    reg(Ops::JSR,     AM::Absolute, 3, 6, &CPU::opJSR);
    reg(Ops::RTS,     AM::Not_addressing, 1, 6, &CPU::opRTS);
    reg(Ops::BRK,     AM::Not_addressing, 1, 7, &CPU::opBRK);
    reg(Ops::RTI,     AM::Not_addressing, 1, 6, &CPU::opRTI);

    reg(Ops::PHA, AM::Not_addressing, 1, 3, &CPU::opPHA);
    reg(Ops::PLA, AM::Not_addressing, 1, 4, &CPU::opPLA);
    reg(Ops::PHP, AM::Not_addressing, 1, 3, &CPU::opPHP);
    reg(Ops::PLP, AM::Not_addressing, 1, 4, &CPU::opPLP);

    // --- Flags ---
    reg(Ops::CLC, AM::Not_addressing, 1, 2, &CPU::opCLC);
    reg(Ops::CLD, AM::Not_addressing, 1, 2, &CPU::opCLD);
    reg(Ops::CLI, AM::Not_addressing, 1, 2, &CPU::opCLI);
    reg(Ops::CLV, AM::Not_addressing, 1, 2, &CPU::opCLV);
    reg(Ops::SEC, AM::Not_addressing, 1, 2, &CPU::opSEC);
    reg(Ops::SED, AM::Not_addressing, 1, 2, &CPU::opSED);
    reg(Ops::SEI, AM::Not_addressing, 1, 2, &CPU::opSEI);

    // --- Branch ---
    reg(Ops::BPL, AM::Relative, 2, 2, &CPU::opBPL);
    reg(Ops::BMI, AM::Relative, 2, 2, &CPU::opBMI);
    reg(Ops::BVC, AM::Relative, 2, 2, &CPU::opBVC);
    reg(Ops::BVS, AM::Relative, 2, 2, &CPU::opBVS);
    reg(Ops::BCC, AM::Relative, 2, 2, &CPU::opBCC);
    reg(Ops::BCS, AM::Relative, 2, 2, &CPU::opBCS);
    reg(Ops::BNE, AM::Relative, 2, 2, &CPU::opBNE);
    reg(Ops::BEQ, AM::Relative, 2, 2, &CPU::opBEQ);
}

#endif // OPCODES_H