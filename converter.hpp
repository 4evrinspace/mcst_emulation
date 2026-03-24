#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace Converter {
// структура для именновоного доступа к байтам чтобы не запутаться
struct Converted_line {
    char opcode, destination, left_operand, right_operand;
};

// строка ассемблера -> в стркоу байткода
Converted_line convert_from_textline(const std::string&);

// вектор строк в байткода записать в файл
void translate_asm(const std::vector<Converted_line>&, std::fstream&);

void translate_asm(const std::vector<Converted_line>&);
};  
// namespace Converter