#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include "../src/cpu/cpu.h"
#include "../src/bus/bus.h"

struct LogState {
    uint16_t pc;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t p;
    uint8_t sp;
    uint64_t cyc;
};

LogState parseLogLine(const std::string& line) {
    LogState state;
    state.pc = std::stoi(line.substr(0, 4), nullptr, 16);
    
    auto posA = line.find("A:");
    state.a = std::stoi(line.substr(posA + 2, 2), nullptr, 16);
    
    auto posX = line.find("X:");
    state.x = std::stoi(line.substr(posX + 2, 2), nullptr, 16);
    
    auto posY = line.find("Y:");
    state.y = std::stoi(line.substr(posY + 2, 2), nullptr, 16);
    
    auto posP = line.find("P:");
    state.p = std::stoi(line.substr(posP + 2, 2), nullptr, 16);
    
    auto posSP = line.find("SP:");
    state.sp = std::stoi(line.substr(posSP + 3, 2), nullptr, 16);
    
    auto posCYC = line.find("CYC:");
    state.cyc = std::stoull(line.substr(posCYC + 4));
    
    return state;
}

TEST(CPU, Nestest_Run)
{
    Bus bus;
    CPU cpu(bus);

    auto cart = std::make_shared<Cartridge>("../../nestest.nes");
    ASSERT_TRUE(cart->ImageValid());

    bus.insertCartridge(cart);

    cpu.reset();
    cpu.setPC(0xC000);

    std::ifstream logFile("../nestest.log");
    ASSERT_TRUE(logFile.is_open()) << "Failed to open nestest.log";

    std::string line;
    int lineNum = 1;
    
    uint64_t initial_log_cyc = 7;
    uint64_t initial_cpu_cyc = cpu.getCycles();
    uint64_t actual_adjusted_cyc = 0;
    
    std::map<std::string, int> opcodeCoverage;
    
    while (std::getline(logFile, line)) {
        if (line.empty()) continue;
        
        LogState expected = parseLogLine(line);
        
        std::string mnemonic = line.substr(16, 3);
        if (mnemonic[0] == '*') {
            mnemonic = line.substr(17, 3);
        }
        opcodeCoverage[mnemonic]++;

        EXPECT_EQ(cpu.getPC(), expected.pc) << "PC mismatch at line " << lineNum;
        EXPECT_EQ(cpu.getRegister('A'), expected.a) << "A mismatch at line " << lineNum;
        EXPECT_EQ(cpu.getRegister('X'), expected.x) << "X mismatch at line " << lineNum;
        EXPECT_EQ(cpu.getRegister('Y'), expected.y) << "Y mismatch at line " << lineNum;
        EXPECT_EQ(cpu.getFlags().raw(), expected.p) << "P mismatch at line " << lineNum;
        EXPECT_EQ(cpu.getRegister('S'), expected.sp) << "SP mismatch at line " << lineNum;
        
        uint64_t expected_adjusted_cyc = expected.cyc - initial_log_cyc;
        EXPECT_EQ(actual_adjusted_cyc, expected_adjusted_cyc) << "Cycle mismatch at line " << lineNum;

        if (::testing::Test::HasFailure()) {
            std::cout << "FAILED AT LINE: " << lineNum << "\n" << line << "\n";
            break;
        }

        actual_adjusted_cyc += cpu.executeInstruction();
        lineNum++;
        
        if (lineNum > 5003) break; 
    }

    
    std::ofstream reportFile("nestest_allure_metrics.json");
    reportFile << "{\n";
    reportFile << "  \"total_instructions_tested\": " << (lineNum - 1) << ",\n";
    reportFile << "  \"instruction_counts\": {\n";
    
    std::cout << "\n============================================\n";
    std::cout << " NESTEST OFFICIAL INSTRUCTION COVERAGE\n";
    std::cout << "============================================\n";
    
    RecordProperty("Total_Instructions_Executed", lineNum - 1);

    for (auto it = opcodeCoverage.begin(); it != opcodeCoverage.end(); ++it) {
        reportFile << "    \"" << it->first << "\": " << it->second;
        if (std::next(it) != opcodeCoverage.end()) reportFile << ",";
        reportFile << "\n";
        
        RecordProperty(("Mnemonic_" + it->first).c_str(), it->second);
        
        std::cout << "  " << std::setw(3) << it->first << " : ";
        int bars = (it->second / 15) + 1; 
        for(int i=0; i<bars; ++i) std::cout << "#";
        std::cout << " (" << it->second << ")\n";
    }
    std::cout << "============================================\n";
    
    reportFile << "  }\n";
    reportFile << "}\n";

    SUCCEED();
}