#include <bits/stdc++.h>

#include "converter.hpp"
#include "emulator.hpp"

using namespace std;

int main() {
    vector<string> string_commands{"LI R0 0x1", "LI R1 0x7000", "ADD R2 R1 R0"};
    vector<converter::Converted_line> commands;
    for (const string& i : string_commands) {
        commands.push_back(converter::convert_from_textline(i));
    }
    converter::translate_asm(commands);
    std::fstream file;
    file.open("out.o", std::ios::binary | std::ios::in);
    std::vector<converter::Converted_line> extracted_lines = converter::extract_from_binary(file);
    file.close();
    emulator::Emulator emul;
    for (converter::Converted_line& i : extracted_lines) {
        emul.execute(i);
    }
    assert(emul.registers[0] == 1);
    assert(emul.registers[1] == 0x7000);
    assert(emul.registers[2] == 0x7001);
    std::cout << emul.print();   
}