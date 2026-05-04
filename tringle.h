#pragma once
#include "point.h"
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
    Triangle(const Point& p1,const Point& p2,const Point& p3);

    /**
     * @brief Нахождение координат точки H
     */
    Point getPointH() const;

    /**
     * @brief Расчет площади треугольника
     */
    double getPlo() const;
};
