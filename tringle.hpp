#pragma once
#include "point.hpp"
/**
 * @brief Класс треугольник
 */
class Triangle
{
private:
    /**
     * @brief Первая вершина
     */
    Point p1;
    /**
     * @brief Вторая вершина
     */
    Point p2;
    /**
     * @brief Третья вершина
     */
    Point p3;

public:
    /**
     * @brief Конструктор
     * @param p1 - первая точка
     * @param p2 - вторая точка
     * @param p3 - третья точка
     */
    Triangle(Point p1, Point p2, Point p3);

    /**
     * @brief Нахождение координат точки H
     */
    Point getPointH() const;

    /**
     * @brief Расчет площади треугольника
     */
    double getPlo() const;
};
