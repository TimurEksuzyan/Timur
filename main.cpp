#include <iostream>
#include <string>     
#include "tringle.h"  
#include "point.h"

/**
 * @brief Запрашивает у пользователя координаты точки
 * @param pointName - имя точки (например, "p1")
 * @return Point - введённая точка
 */
Point getPoint(const std::string& pointName);

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    Point p1 = getPoint("p1");
    Point p2 = getPoint("p2");
    Point p3 = getPoint("p3");
    Triangle myTriangle(p1, p2, p3);
    Point H = myTriangle.getPointH();
    std::cout << "Координаты точки H: X = " << H.getX() << ", Y = " << H.getY() << std::endl;
    std::cout << "Площадь равна: " << myTriangle.getPlo() << std::endl;
    
    return 0;
}

Point getPoint(const std::string& pointName)
{
    double x, y;
    
    std::cout << "Введите координаты точки " << pointName << ":" << std::endl;
    std::cout << "  x = ";
    std::cin >> x;
    std::cout << "  y = ";
    std::cin >> y;
    if (std::cin.fail()) {
        std::cout << "Ошибка ввода! Программа завершена." << std::endl;
        exit(1);
    }
    
    return Point(x, y);
}
