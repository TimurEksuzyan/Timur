#pragma once
#include <iostream>
#include <initializer_list>
#include <string>

/**
 * @brief Класс Стек (Stack)
 */
class Stack
{
private:
    /**
     * @brief Указатель на динамический массив элементов стека.
     */
    int *m_elements;

    /**
     * @brief Текущее количество элементов в стеке.
     */
    size_t m_count;

public:
    /**
     * @brief Конструктор по умолчанию. Создает пустой стек.
     */
    Stack();

    /**
     * @brief Конструктор со списком инициализации.
     * @param items Список инициализации (std::initializer_list) для заполнения стека.
     */
    Stack(const std::initializer_list<int> items);

    /**
     * @brief Конструктор копирования.
     * @param other Стек, глубокая копия которого создается.
     */
    Stack(const Stack &other);

    /**
     * @brief Конструктор перемещения.
     * @param other Стек, ресурсы которого перемещаются в новый объект.
     */
    Stack(Stack &&other);

    /**
     * @brief Деструктор. Освобождает выделенную память массива.
     */
    ~Stack();

    /**
     * @brief Возвращает строковое представление содержимого стека.
     * @return Строка с элементами стека, разделенными пробелом, или "Empty", если стек пуст.
     */
    std::string to_string() const;

    /**
     * @brief Возвращает текущий размер стека.
     * @return Количество элементов (size_t) в стеке.
     */
    size_t get_size() const;

    /**
     * @brief Проверяет, пуст ли стек.
     * @return true, если стек пуст (размер равен 0), иначе false.
     */
    bool is_empty() const;

    /**
     * @brief Добавляет элемент на вершину стека (операция push).
     * @param value Целочисленное значение, которое нужно добавить.
     */
    void push(const int value);

    /**
     * @brief Удаляет верхний элемент стека (операция pop).
     * @throw std::out_of_range Если стек пуст и удаление невозможно.
     */
    void pop();

    /**
     * @brief Читает верхний элемент стека без его удаления (операция peek).
     * @return Значение элемента на вершине стека.
     * @throw std::out_of_range Если стек пуст.
     */
    int peek() const;

    /**
     * @brief Оператор присваивания (копированием).
     * @param other Объект стека, данные которого копируются.
     * @return Ссылка на текущий измененный объект (*this).
     */
    Stack &operator=(const Stack &other);

    /**
     * @brief Оператор присваивания (перемещением).
     * @param other Объект стека, ресурсы которого забираются.
     * @return Ссылка на текущий измененный объект (*this).
     */
    Stack &operator=(Stack &&other);

    /**
     * @brief Перегрузка оператора вывода в поток (переопределение сдвига влево).
     * @param os Выходной поток (например, std::cout).
     * @param st Стек, содержимое которого выводится.
     * @return Ссылка на выходной поток для цепочечных вызовов.
     */
    friend std::ostream &operator<<(std::ostream &os, const Stack &st);

    /**
     * @brief Перегрузка оператора ввода из потока (переопределение сдвига вправо).
     * @param is Входной поток (например, std::cin).
     * @param st Стек, в который добавляется считанное значение.
     * @return Ссылка на входной поток для цепочечных вызовов.
     */
    friend std::istream &operator>>(std::istream &is, Stack &st);
};
