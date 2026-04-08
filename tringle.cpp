#include <iostream>
#include <cmath>
#include "tringle.hpp"
Triangle::Triangle(Point p1, Point p2, Point p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    if (p1 == p2 || p2 == p3 || p1 == p3)
    {
        std::cout << "Ошибка: Точки совпадают!" << std::endl;
        exit(1);
    }
    if (this->getPlo() == 0)
    {
        std::cout << "Ошибка: Треугольник не существует." << std::endl;
        exit(1);
    }
    double check = (p3.getX() - p1.getX()) * (p2.getY() - p1.getY()) - (p3.getY() - p1.getY()) * (p2.getX() - p1.getX());
    if (check == 0)
    {
        std::cout << "Ошибка! Третья точка лежит на той же прямой, что и первые две!" << std::endl;
        exit(1);
    }
}

Point Triangle::getPointH() const
{
    double BCx = p3.getX() - p2.getX();
    double BCy = p3.getY() - p2.getY();
    double BAx = p1.getX() - p2.getX();
    double BAy = p1.getY() - p2.getY();
    double t = (BAx * BCx + BAy * BCy) / (BCx * BCx + BCy * BCy);
    double hx = p2.getX() + t * BCx;
    double hy = p2.getY() + t * BCy;
    return Point(hx, hy);
}

double Triangle::getPlo() const
{
    return fabs((p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p3.getX() - p1.getX()) * (p2.getY() - p1.getY())) / 2.0;
}
