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
     * @brief Указатель на динамический массив элементов
     */
    int *m_elements;

    /**
     * @brief Количество элементов в стеке
     */
    size_t m_count;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Stack();
    /**
     * @brief Конструктор со списком инициализации
     */
    Stack(const std::initializer_list<int> items);
    /**
     * @brief Конструктор копирования
     */
    Stack(const Stack &other);
    /**
     * @brief Конструктор перемещения
     */
    Stack(Stack &&other);
    /**
     * @brief Деструктор
     */
    ~Stack();

    /**
     * @brief Возвращает строку с содержимым коллекции
     */
    std::string to_string() const;
    /**
     * @brief Возвращает текущий размер
     */
    size_t get_size() const;
    /**
     * @brief Проверка коллекции на пустоту
     */
    bool is_empty() const;

    /**
     * @brief Добавление элемента на вершину стека (push)
     * @param value новое значение
     */
    void push(const int value);
    /**
     * @brief Удаление верхнего элемента стека (pop)
     */
    void pop();
    /**
     * @brief Чтение верхнего элемента стека (peek)
     * @return значение верхнего элемента
     */
    int peek() const;

    /**
     * @brief Оператор присваивания (копирование)
     */
    Stack &operator=(const Stack &other);
    /**
     * @brief Оператор присваивания (перемещение)
     */
    Stack &operator=(Stack &&other);

    /**
     * @brief Перегрузка оператора сдвига влево (вывод)
     */
    friend std::ostream &operator<<(std::ostream &os, const Stack &st);
    /**
     * @brief Перегрузка оператора сдвига вправо (ввод)
     */
    friend std::istream &operator>>(std::istream &is, Stack &st);
};