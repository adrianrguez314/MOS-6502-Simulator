cmake_minimum_required(VERSION 3.14)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

include(FetchContent)

FetchContent_Declare(
  SDL2
  URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-2.28.5.zip
)

message(STATUS "Download and install SDL2. Wait a moment...")
FetchContent_MakeAvailable(SDL2)

file(GLOB CPU_SOURCES 
    "src/core/6502/*.cpp"
    "src/core/6502/instructions/*.cpp"
    "src/system/bus/*.cpp"
    "src/system/cartridge/*.cpp"
    "src/core/ppu/*.cpp"
    "src/core/render/*.cpp"
)
list(FILTER CPU_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(emulator_lib ${CPU_SOURCES})


target_link_libraries(emulator_lib PRIVATE SDL2::SDL2-static)
target_include_directories(emulator_lib PRIVATE "${SDL2_SOURCE_DIR}/include")


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/nestest.log")
    file(DOWNLOAD "https://raw.githubusercontent.com/christopherpow/nes-test-roms/master/other/nestest.log" "${CMAKE_SOURCE_DIR}/nestest.log")
endif()

file(GLOB TEST_FILES "tests/integration/*.cpp" "tests/unit/system/*.cpp" "tests/unit/core/6502/*.cpp" "tests/unit/core/6502/instructions/*.cpp")

add_executable(unit_tests ${TEST_FILES})
target_link_libraries(unit_tests PRIVATE emulator_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)


add_executable(main src/main.cpp)

target_link_libraries(main 
    PRIVATE 
    emulator_lib 
    SDL2::SDL2-static
    SDL2::SDL2main
)
