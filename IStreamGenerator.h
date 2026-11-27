#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Генератор, считывающий целые числа из входного потока
     */
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор потокового генератора
         * @param in Входной поток (по умолчанию std::cin)
         */
        IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Считывает следующее целое число из потока
         * @return Считанное значение
         */
        int generate() override;
    };
}
