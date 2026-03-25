#include <bits/stdc++.h>

#include "converter.hpp"
using namespace std;

int main() {
    vector<string> string_commands{"LI R0 0x1", "LI R1 0x7000", "ADD R1 R1 R0"};
    vector<converter::Converted_line> commands;
    std::array<char, 12> expected = {0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
                                     0x00, 0x70, 0x02, 0x01, 0x01, 0x00};
    for (const string& i : string_commands) {
        commands.push_back(converter::convert_from_textline(i));
    }
    converter::translate_asm(commands);
    std::array<char, 12> ans_read;
    std::fstream file;
    file.open("out.o", std::ios::binary | std::ios::in);
    for (char& i : ans_read) {
        file.read(&i, 1);
    }

    file.close();
    assert(ans_read == expected);
}