#include "converter.hpp"

#include <bits/stdc++.h>

bool equals(char* left, char* right, int size) {
    for (int i = 0; i < size; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}


using namespace std;
int main () {
    vector<string> string_commands{"LI R0 0x1", "LI R1 0x7000", "ADD R1 R1 R0"};
    vector<Converter::Converted_line> commands;
    char expected[12] =  {0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x70, 0x02, 0x01, 0x01, 0x00};
    for (const string& i: string_commands) {
        commands.push_back(Converter::convert_from_textline(i));
    }
    Converter::translate_asm(commands);
    char ans_read[12];
    std::fstream file;
    file.open("out.o",std::ios::binary | std::ios::in);
    file.read(ans_read, 12);
    file.close();
    assert(equals(ans_read, expected, 12));
}