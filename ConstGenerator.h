#pragma once
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, возвращающий фиксированное константное значение
     */
    class ConstGenerator : public Generator
    {
    private:
        int value;

    public:
        /**
         * @brief Конструктор генератора константы
         * @param val Константное значение (по умолчанию 0)
         */
        ConstGenerator(const int val = 0);

        /**
         * @brief Возвращает константное значение
         * @return Сохраненное значение
         */
        int generate() override;
    };
}
