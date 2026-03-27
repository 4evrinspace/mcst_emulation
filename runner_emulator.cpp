#include <iostream>
#include <vector>
#include <string>

#include "converter.hpp"
#include "emulator.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr
            << "Need to pass file: <binary input file>"
            << std::endl;
        return 1;
    }
    std::fstream binary_input;
    binary_input.open(argv[1], std::ios::in | std::ios::binary);
    if (!binary_input.is_open()) {
        std::cerr << "Can't open binary input file" << std::endl;
        return 1;
    }
    const std::vector<converter::Converted_line>& commands = converter::extract_from_binary(binary_input);

    emulator::Emulator emulator;

    for (const converter::Converted_line& command_line : commands) {
        emulator.execute(command_line);
    }

    std::cout << emulator.print() << std::endl;

    
    binary_input.close();
}