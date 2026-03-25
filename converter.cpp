#include "converter.hpp"

#include <iostream>
#include <regex>
#include <stdexcept>

namespace converter {

Converted_line convert_from_textline(const std::string& input_line) {
    // это регулярное выражение ловит строки вида LI R* 0xAAAA где
    //  * - число в [0, 15]
    //  0xAAAA - двухбайтовое число (сделал, что ловит все регистры)
    std::regex load_regex(R"(^LI R([0-9]|1[0-5]) (0x[0-9A-Fa-f]{1,4})$)");

    // здесь уже ловится строки вида ADD Ra Rb Rc  где
    // a b c - числа в [0, 15]
    std::regex add_regex(
        R"(^ADD R([0-9]|1[0-5]) R([0-9]|1[0-5]) R([0-9]|1[0-5])$)");

    std::smatch matched_groups;

    if (std::regex_match(input_line, matched_groups, load_regex)) {
        int load_number = std::stoi(matched_groups[2], nullptr, 16);
        return Converted_line{
            .opcode = 0,
            .destination = (char)std::stoi(matched_groups[1]),
            .left_operand = (char)(load_number & 255),         // младший байт
            .right_operand = (char)((load_number >> 8) & 255)  // старший байт

        };
    } else if (std::regex_match(input_line, matched_groups, add_regex)) {
        return Converted_line{
            .opcode = 2,
            // ADD Ra Rb Rc : a-> matched_groups[1], b-> matched_groups[2],
            // c->matched_groups[3]
            .destination = (char)std::stoi(matched_groups[1]),
            .left_operand = (char)std::stoi(matched_groups[2]),
            .right_operand = (char)std::stoi(matched_groups[3])

        };
    } else {
        throw("Unknown operation , line passed: " + input_line);
    }
}

void translate_asm(const std::vector<Converted_line>& converted_lines,
                   std::fstream& file) {
    for (const Converted_line& i : converted_lines) {
        file.write((char*)&i, sizeof(Converted_line));
    }
}

void translate_asm(const std::vector<Converted_line>& converted_lines) {
    std::fstream file("out.o", std::ios::out | std::ios::binary);
    translate_asm(converted_lines, file);
    file.close();
}

std::vector<Converted_line> extract_from_binary(std::fstream& file) {
    Converted_line buffer;
    std::vector<Converted_line> ans;
    while (file.read((char*)&buffer, sizeof(buffer))) {
        ans.push_back(buffer);
    }
    return ans;
}

};  // namespace converter