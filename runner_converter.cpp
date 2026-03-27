#include <iostream>
#include <string>
#include <vector>

#include "converter.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr
            << "Need to pass 2 files: <assembler input> <name of output file>"
            << std::endl;
        return 1;
    }
    std::fstream assembler_input;
    assembler_input.open(argv[1], std::ios::in);
    if (!assembler_input.is_open()) {
        std::cerr << "Can't open assembler input file" << std::endl;
        return 1;
    }
    std::fstream binary_output;
    binary_output.open(argv[2], std::ios::out | std::ios::binary);
    if (!binary_output.is_open()) {
        std::cerr << "Can't open binary output file" << std::endl;
        return 1;
    }

    std::vector<converter::Converted_line> converted_commands;

    std::string line;

    while (std::getline(assembler_input, line)) {
        converted_commands.emplace_back(converter::convert_from_textline(line));
    }

    converter::translate_asm(converted_commands, binary_output);

    assembler_input.close();
    binary_output.close();
}