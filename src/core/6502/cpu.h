#ifndef cpu_h
#define cpu_h 

#include <iostream>
#include <cstdint>
#include <functional>

#include "../../system/bus/bus.h"
#include "flags.h"

struct Instruction;

class CPU {

    Bus& bus;

    public:
        CPU(Bus& Bus);
        ~CPU();
        void reset();
        int executeInstruction();
        void run(int cycles_to_execute);
        void branchRelative(bool condition);

        enum class AddressingMode {
            Immediate,
            ZeroPage, ZeroPage_X, ZeroPage_Y,
            Absolute, Absolute_X, Absolute_Y,
            Indirect, Indirect_X, Indirect_Y,
            Accumulator,
            Relative,
            Not_addressing,
        };

        static constexpr uint16_t STACK_BASE = 0x0100;
        static constexpr uint8_t  STACK_RESET_POINTER = 0xFD;
        static constexpr uint8_t  STATUS_RESET_VALUE = 0x24;

        uint16_t getAddress(AddressingMode mode);

        void setA(uint8_t v) { registers.A = v; }
        void setX(uint8_t v) { registers.X = v; }
        void setY(uint8_t v) { registers.Y = v; }
        void setSP(uint8_t v) { registers.SP = v; }

        
        uint8_t getRegister(char registerName) const;

        void setPC(uint16_t v) { registers.PC = v; }
        uint16_t getPC() { return registers.PC; }

        void pushStack(uint8_t value);
        uint8_t pullStack();

        Flags& getFlags() { return registers.P; }
        const Flags& getFlags() const { return registers.P; }

        uint64_t getCycles() const { return total_cycles; }
        void tick(int cycles = 1) { extra_cycles += cycles; }
        bool isInstructionComplete() const { return cycles_remaining == 0; }

        void trace(std::ostream& os = std::cout);
        void setDebugMode(bool state) { debug_enabled = state; }


        void opLDA(AddressingMode mode); void opLDX(AddressingMode mode); void opLDY(AddressingMode mode);
        void opSTA(AddressingMode mode); void opSTX(AddressingMode mode); void opSTY(AddressingMode mode);
        void opTAX(AddressingMode mode); void opTAY(AddressingMode mode); void opTXA(AddressingMode mode); void opTYA(AddressingMode mode);
        void opADC(AddressingMode mode); void opSBC(AddressingMode mode); void opINC(AddressingMode mode); void opDEC(AddressingMode mode);
        void opINX(AddressingMode mode); void opDEX(AddressingMode mode); void opINY(AddressingMode mode); void opDEY(AddressingMode mode);
        void opCMP(AddressingMode mode); void opCPX(AddressingMode mode); void opCPY(AddressingMode mode);
        void opJMP(AddressingMode mode); void opJSR(AddressingMode mode); void opRTS(AddressingMode mode); void opBRK(AddressingMode mode); void opRTI(AddressingMode mode);
        void opCLC(AddressingMode mode); void opCLD(AddressingMode mode); void opCLI(AddressingMode mode); void opCLV(AddressingMode mode); void opSEC(AddressingMode mode); 
        void opSED(AddressingMode mode); void opSEI(AddressingMode mode);
        void opPHA(AddressingMode mode); void opPLA(AddressingMode mode); void opPHP(AddressingMode mode); void opPLP(AddressingMode mode); void opTXS(AddressingMode mode);
        void opTSX(AddressingMode mode);
        void opAND(AddressingMode mode); void opORA(AddressingMode mode); void opEOR(AddressingMode mode); void opBIT(AddressingMode mode);
        void opASL(AddressingMode mode); void opLSR(AddressingMode mode); void opROL(AddressingMode mode); void opROR(AddressingMode mode);
        void opBPL(AddressingMode mode); void opBMI(AddressingMode mode); void opBVC(AddressingMode mode); void opBVS(AddressingMode mode); void opBCC(AddressingMode mode); 
        void opBCS(AddressingMode mode); void opBNE(AddressingMode mode); void opBEQ(AddressingMode mode);
        void opNOP(AddressingMode mode);

        protected:
            struct Registers {
                uint8_t A, X, Y;  // A, X, Y registers
                uint16_t PC;     // Program Counter
                uint8_t SP;     // Stack Pointer
                Flags P;
            } registers;
            long long total_cycles = 0;
            int cycles_remaining = 0;
            int extra_cycles = 0; 
            bool page_crossed = false;
        private:
            uint8_t fetch();
            const Instruction& decode(uint8_t opcode);
            void execute(const Instruction& instr);
            bool debug_enabled = false;
};
#endif // cpu_h
