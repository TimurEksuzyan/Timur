#include <iostream>
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

/**
 * @brief Выбор метода заполнения матрицы
 */
enum FillMethod { RANDOM = 1, MANUAL = 2, CONSTANT = 3 };

/**
 * @brief Запускает решение первой и второй задач с заданным генератором
 * @param rows Количество строк матрицы
 * @param cols Количество столбцов матрицы
 * @param generator Объект генератора значений
 * @param isManual Признак ручного ввода элементов
 */
template <typename GeneratorType>
void runTasks(const size_t rows, const size_t cols, GeneratorType& generator, const bool isManual)
{
    std::cout << "\n ЗАДАЧА 1 \n";
    Task1 task1(rows, cols, generator);
    std::cout << "Исходная матрица:\n" << task1.getMatrix();
    task1.solve();
    std::cout << "Результат задачи 1 (Заменить минимальный по модулю элемент столбца нулем):\n" << task1.getMatrix();

    std::cout << "\n ЗАДАЧА 2 \n";
    if (isManual) {
        std::cout << "Введите элементы матрицы еще раз для задачи 2:\n";
    }

    Task2 task2(rows, cols, generator);
    std::cout << "Исходная матрица:\n" << task2.getMatrix();
    task2.solve();
    std::cout << "Результат задачи 2 (Удалить столбцы, где первый элемент больше последнего):\n" << task2.getMatrix();
}

/**
 * @brief Точка входа в программу
 * @return Код завершения программы (0 — успех, 1 — некорректный выбор способа заполнения)
 */
int main()
{
    size_t rows = 0;
    size_t cols = 0;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    std::cout << "Выберите способ заполнения:\n"
        << FillMethod::RANDOM << " - Случайными числами\n"
        << FillMethod::MANUAL << " - Вручную\n"
        << FillMethod::CONSTANT << " - Константным значением\n";
    int choiceInput = 0;
    std::cin >> choiceInput;

    switch (choiceInput) {
    case FillMethod::RANDOM: {
        int min = 0;
        int max = 0;
        std::cout << "Введите начало диапазона: ";
        std::cin >> min;
        std::cout << "Введите конец диапазона: ";
        std::cin >> max;
        RandomGenerator randomGen(min, max);
        runTasks(rows, cols, randomGen, false);
        break;
    }
    case FillMethod::MANUAL: {
        std::cout << "Введите элементы матрицы:\n";
        IStreamGenerator streamGen(std::cin);
        runTasks(rows, cols, streamGen, true);
        break;
    }
    case FillMethod::CONSTANT: {
        int val = 0;
        std::cout << "Введите константное значение: ";
        std::cin >> val;
        ConstGenerator constGen(val);
        runTasks(rows, cols, constGen, false);
        break;
    }
    default: {
        std::cout << "Неверный выбор заполнения\n";
        return 1;
    }
    }

    return 0;
}
