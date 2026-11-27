#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Generator.h"

namespace miit::algebra
{

    /**
     * @brief Шаблонный класс матрицы
     * @tparam T Тип элементов матрицы
     */
    template <typename T>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> data;
        size_t rows;
        size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию (создает пустую матрицу 0x0)
         */
        Matrix() : rows(0), cols(0) {}

        /**
         * @brief Конструктор с параметрами
         * @param r Количество строк
         * @param c Количество столбцов
         */
        Matrix(const size_t r, const size_t c)
            : rows(r), cols(c), data(r, std::vector<T>(c)) {
        }

        /**
         * @brief Деструктор по умолчанию
         */
        ~Matrix() = default;

        /**
         * @brief Конструктор копирования
         * @param other Копируемая матрица
         */
        Matrix(const Matrix&) = default;

        /**
         * @brief Конструктор перемещения
         * @param other Перемещаемая матрица
         */
        Matrix(Matrix&&) noexcept = default;

        /**
         * @brief Оператор присваивания копированием
         * @param other Копируемая матрица
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator=(const Matrix&) = default;

        /**
         * @brief Оператор присваивания перемещением
         * @param other Перемещаемая матрица
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator=(Matrix&&) noexcept = default;

        /**
         * @brief Оператор индексации строки (неконстантный)
         * @param r Индекс строки
         * @return Ссылка на вектор строки
         */
        std::vector<T>& operator[](const size_t r)
        {
            if (r >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }

        /**
         * @brief Оператор индексации строки (константный)
         * @param r Индекс строки
         * @return Константная ссылка на вектор строки
         */
        const std::vector<T>& operator[](const size_t r) const
        {
            if (r >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы!");
            }
            return data[r];
        }

        /**
         * @brief Получить количество строк матрицы
         * @return Количество строк
         */
        size_t getRows() const { return rows; }

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        size_t getCols() const { return cols; }

        /**
         * @brief Заполнение матрицы с использованием ссылки на генератор
         * @param generator Ссылка на объект генератора
         */
        void fill(const Generator& generator)
        {
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Метод вывода содержимого матрицы в строку
         * @return Строковое представление матрицы
         */
        std::string toString() const
        {
            std::ostringstream oss;
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    oss << data[i][j] << "\t";
                }
                oss << "\n";
            }
            return oss.str();
        }

        /**
         * @brief Удаляет столбец матрицы по указанному индексу
         * @param colIndex Индекс удаляемого столбца
         */
        void removeColumn(const size_t colIndex)
        {
            if (colIndex >= cols) {
                throw std::out_of_range("Индекс столбца выходит за границы матрицы");
            }
            for (size_t i = 0; i < rows; ++i) {
                data[i].erase(data[i].begin() + colIndex);
            }
            cols--;
            if (cols == 0) {
                data.clear();
                rows = 0;
            }
        }

        /**
         * @brief Получение копии указанной строки матрицы
         * @param index Индекс строки
         * @return Вектор элементов запрошенной строки
         */
        std::vector<T> getRow(const size_t index) const
        {
            if (index >= rows) {
                throw std::out_of_range("Индекс строки выходит за границы матрицы");
            }
            return data[index];
        }

        /**
         * @brief Переопределение оператора сдвига влево для вывода матрицы в поток
         * @param os Поток вывода
         * @param matrix Матрица для вывода
         * @return Ссылка на поток вывода
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
        {
            os << matrix.toString();
            return os;
        }

        /**
         * @brief Переопределение оператора сдвига вправо (ввод матрицы из потока)
         * @param is Поток ввода
         * @param matrix Матрица для заполнения
         * @return Ссылка на поток ввода
         */
        friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
        {
            for (size_t i = 0; i < matrix.rows; ++i) {
                for (size_t j = 0; j < matrix.cols; ++j) {
                    is >> matrix.data[i][j];
                }
            }
            return is;
        }

    };
}
