#include <iostream>
#include "tringle.hpp"
#include "point.hpp"
/**
 * @brief Считывает значение, введенное с клавиатуры
 * @param report - строка информации
 * @return считанное значение
 */
double getValue(std::string report = "");
/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    double x1 = getValue("Введите x1: ");
    double y1 = getValue("Введите y1: ");
    double x2 = getValue("Введите x2: ");
    double y2 = getValue("Введите y2: ");
    double x3 = getValue("Введите x3: ");
    double y3 = getValue("Введите y3: ");
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3(x3, y3);
    Triangle myTriangle(p1, p2, p3);
    Point H = myTriangle.getPointH();
    std::cout << "Координаты точки H: X = " << H.getX() << ", Y = " << H.getY() << std::endl;
    std::cout << "Площадь равна: " << myTriangle.getPlo() << std::endl;
    return 0;
}
double getValue(std::string report)
{
    std::cout << report;
    double value = 0;
    std::cin >> value;
    if (std::cin.fail())
    {
        std::cout << "Ошибка, введено неверное значение!\n";
        exit(1);
    }
    return value;
}
