#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор псевдослучайных целых чисел в заданном диапазоне
     */
    class RandomGenerator : public Generator
    {
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 generator;

    public:
        /**
         * @brief Конструктор генератора случайных чисел
         * @param min Нижняя граница диапазона включительно
         * @param max Верхняя граница диапазона включительно
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Генерирует случайное число из заданного диапазона
         * @return Случайное целое число
         */
        int generate() override;
    };
}
