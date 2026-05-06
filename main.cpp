#include <iostream>
#include <string>
#include "triangle.h"
#include "point.h"

/**
 * Считывает число с клавиатуры с проверкой ошибок
 * @param prompt - текст приглашения
 * @return double - введённое число
 */
double readDouble(const std::string& prompt);

/**
 * Запрашивает координаты точки и возвращает объект Point
 * @param pointName - имя точки
 * @return Point - созданная точка
 */
Point getPoint(const std::string& pointName);

int main()
{
    std::cout << "=== Ввод координат треугольника ===" << std::endl;
    
    Point p1 = getPoint("p1");
    Point p2 = getPoint("p2");
    Point p3 = getPoint("p3");
    
    std::cout << std::endl;
    
    Triangle myTriangle(p1, p2, p3);
    Point H = myTriangle.getPointH();
    
    std::cout << "Результаты вычислений:" << std::endl;
    std::cout << "  Координаты точки H:" << std::endl;
    std::cout << "    X = " << H.getX() << std::endl;
    std::cout << "    Y = " << H.getY() << std::endl;
    std::cout << "  Площадь треугольника: " << myTriangle.getPlo() << std::endl;
    
    return 0;
}

double readDouble(const std::string& prompt)
{
    double value;
    std::cout << prompt;
    std::cin >> value;
    
    if (std::cin.fail())
    {
        std::cout << "Ошибка! Введено неверное значение. Программа завершена." << std::endl;
        exit(1);
    }
    
    return value;
}

Point getPoint(const std::string& pointName)
{
    std::cout << "Введите координаты точки " << pointName << ":" << std::endl;
    double x = readDouble("  x = ");
    double y = readDouble("  y = ");
    return Point(x, y);
}
