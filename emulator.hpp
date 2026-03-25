#pragma once

#include <array>
#include <string>

#include "converter.hpp"

namespace emulator {

class Emulator {
   public:
    // инициадизируем нулями
    Emulator() = default;

    // 32-ух разрядные регистры - значит что это буквально интовая переменная
    std::array<int, 16> registers;

    // Возвращает стркоове представление регистров в данный момент времени
    std::string print();

    // Исполнение команды переданной в данном виде
    void execute(converter::Converted_line);
};

}  // namespace emulator