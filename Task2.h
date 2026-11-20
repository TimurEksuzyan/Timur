#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс для реализации второй части задания 
     */
    class Task2 : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task2
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen указатель на генератор
         */
        Task2(const size_t r, const size_t c, Generator& gen);

        /**
         * @brief Выполняет удаление столбцов, в которых первый элемент больше последнего
         */
        void solve() override;
    };
}