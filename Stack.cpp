#include <iostream>
#include "Stack.h"
#include <sstream>
#include <stdexcept>

Stack::Stack() : m_elements(nullptr), m_count(0) {}

Stack::Stack(const std::initializer_list<int> items) : m_elements(nullptr), m_count(items.size())
{
    if (m_count > 0)
    {
        m_elements = new int[m_count];
        size_t idx = 0;
        for (const int &val : items)
        {
            m_elements[idx++] = val;
        }
    }
}

Stack::~Stack()
{
    delete[] m_elements;
}

Stack::Stack(const Stack &other) : m_elements(nullptr), m_count(other.m_count)
{
    if (m_count > 0)
    {
        m_elements = new int[m_count];
        for (size_t i = 0; i < m_count; ++i)
        {
            m_elements[i] = other.m_elements[i];
        }
    }
}

Stack::Stack(Stack &&other) : m_elements(other.m_elements), m_count(other.m_count)
{
    other.m_elements = nullptr;
    other.m_count = 0;
}

std::string Stack::to_string() const
{
    if (is_empty())
        return "Empty";

    std::stringstream ss;
    for (size_t i = 0; i < m_count; ++i)
    {
        ss << m_elements[i];
        if (i < m_count - 1)
            ss << " ";
    }
    return ss.str();
}

size_t Stack::get_size() const
{
    return m_count;
}

bool Stack::is_empty() const
{
    return m_count == 0;
}

void Stack::push(const int value)
{
    int *tempArray = new int[m_count + 1];
    for (size_t i = 0; i < m_count; ++i)
    {
        tempArray[i] = m_elements[i];
    }
    tempArray[m_count] = value;
    
    delete[] m_elements;
    m_elements = tempArray;
    m_count++;
}

void Stack::pop()
{
    if (is_empty())
    {
        throw std::out_of_range("Ошибка: Стек пуст, невозможно удалить элемент!");
    }
    
    int *tempArray = (m_count > 1) ? new int[m_count - 1] : nullptr;
    for (size_t i = 0; i < m_count - 1; ++i)
    {
        tempArray[i] = m_elements[i];
    }
    
    delete[] m_elements;
    m_elements = tempArray;
    m_count--;
}

int Stack::peek() const
{
    if (is_empty())
    {
        throw std::out_of_range("Ошибка: Стек пуст, нет верхнего элемента!");
    }
    return m_elements[m_count - 1];
}

Stack &Stack::operator=(const Stack &other)
{
    if (this != &other)
    {
        delete[] m_elements;
        m_count = other.m_count;
        m_elements = (m_count > 0) ? new int[m_count] : nullptr;
        for (size_t i = 0; i < m_count; ++i)
        {
            m_elements[i] = other.m_elements[i];
        }
    }
    return *this;
}

Stack &Stack::operator=(Stack &&other)
{
    if (this != &other)
    {
        delete[] m_elements;
        m_elements = other.m_elements;
        m_count = other.m_count;
        other.m_elements = nullptr;
        other.m_count = 0;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Stack &st)
{
    os << st.to_string();
    return os;
}

std::istream &operator>>(std::istream &is, Stack &st)
{
    int value = 0;
    if (is >> value)
    {
        st.push(value);
    }
    return is;
}