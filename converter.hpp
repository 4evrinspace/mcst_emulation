#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace converter {
// структура для именновоного доступа к байтам чтобы не запутаться
struct Converted_line {
    char opcode,        // 0 - загрузка, 2 - сложение
        destination,    // номер регистра
        left_operand,   // левый операнд операции (байт или регистр)
        right_operand;  // правый операнд операции (байт или регистр )
};

// строка ассемблера -> в стркоу байткода
Converted_line convert_from_textline(const std::string&);

// вектор строк в байткода файла
void translate_asm(const std::vector<Converted_line>&, std::fstream&);

void translate_asm(const std::vector<Converted_line>&);

// Из бинарного файла в команды
std::vector<Converted_line> extract_from_binary(std::fstream&);

};  // namespace converter