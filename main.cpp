#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack.h"

using namespace std;

/**
 * @brief Нумерация объектов выбора для Стека
 */
enum Actions
{
    PUSH = 1,
    POP,
    PEEK
};

/**
 * @brief Выводит ошибку и завершает работу программы
 * @param text - текст, выводимый на экран
 */
void ERROR(const string text)
{
    cerr << text << endl;
    exit(1);
}

/**
 * @brief Считывает значение, введенное с клавиатуры
 * @return считанное значение
 */
int get_choice()
{
    int number = 0;
    cin >> number;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return number;
}

/**
 * @brief Точка входа в программу
 * @return Если программа выполнена корректно - 0, иначе 1
 */
int main()
{
    Stack collection;
    cout << "Укажите начальное количество элементов стека: ";
    int n = get_choice();
    if (n < 0)
    {
        ERROR("Ошибка: количество элементов не может быть отрицательным.");
    }
    if (n > 0)
    {
        cout << "Введите " << n << " элементов стека (через пробел или Enter): " << endl;
        for (size_t i = 0; i < static_cast<size_t>(n); ++i)
        {
            int val = get_choice();
            collection.push(val);
        }
    }
    
    cout << "Изначальный стек (от нижнего к верхнему): " << collection << endl;
    cout << "Выберите действие со стеком: " << endl
         << PUSH << " - Добавить элемент на вершину (Push)" << endl
         << POP  << " - Удалить элемент с вершины (Pop)" << endl
         << PEEK << " - Посмотреть верхний элемент (Peek)" << endl;
         
    cout << "Ваш выбор: ";
    int choice = get_choice();
    
    try
    {
        switch (choice)
        {
        case PUSH:
        {
            cout << "Введите значение для добавления: ";
            int val = get_choice();
            collection.push(val);
            cout << "После добавления: " << collection << endl;
            break;
        }
        case POP:
        {
            collection.pop();
            cout << "После удаления верхнего элемента: " << collection << endl;
            break;
        }
        case PEEK:
        {
            int top_val = collection.peek();
            cout << "Элемент на вершине стека равен: " << top_val << endl;
            break;
        }
        default:
            ERROR("Ошибка: Неверный выбор пункта меню.");
        }
    }
    catch (const exception &e)
    {
        cout << "Ошибка! " << e.what() << endl;
    }
    
    if (!collection.is_empty())
    {
        cout << endl << "Текущий размер стека: " << collection.get_size() << " элементов." << endl;
    }
    
    return 0;
}