#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный базовый класс генератора целых чисел
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор по умолчанию
         */
        virtual ~Generator() = default;

        /**
         * @brief Генерирует следующее целое число
         * @return Сгенерированное значение
         */
        virtual int generate() = 0;
    };
}
