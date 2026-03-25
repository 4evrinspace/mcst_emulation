#include "emulator.hpp"

#include <sstream>
#include <string>

namespace emulator {

std::string Emulator::print() {
    std::stringstream stream;
    for (int i = 0; i < 15; i++) {
        stream << "R" << i << "=0x" << std::hex << registers[i] << ", ";
    }
    stream << "R" << 15 << "=0x" << std::hex << registers[15];
    return stream.str();
}

void Emulator::execute(converter::Converted_line command) {
    if (command.opcode == 0) {  // Загрузка
        if (command.destination > 15) {
            throw std::invalid_argument(
                "Passed non-existring register to command");
        }
        registers[command.destination] =
            command.left_operand | (command.right_operand << 8);
    } else if (command.opcode == 2) {  // Сложение
        if (command.destination > 15 || command.left_operand > 15 ||
            command.right_operand > 15) {
            throw std::invalid_argument(
                "Passed non-existring register to command");
        }
        registers[command.destination] =
            registers[command.left_operand] + registers[command.right_operand];
    } else {
        throw std::invalid_argument("Unknown opcode was passed");
    }
}

};  // namespace emulator
