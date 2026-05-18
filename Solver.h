#pragma once
/**
 * @brief Абстрактный базовый класс для численных методов
 */
class Solver
{
public:
    virtual ~Solver() = default;
    /**
     * @brief Абстрактный метод решения
     * @param x точка, в которой вычисляется производная
     * @param unused неиспользуемый параметр (для совместимости)
     * @param h шаг приращения
     * @param f заданная функция
     * @return значение производной
     */
    virtual double solve(const double x, const double unused, const double h, double (*f)(double)) const = 0;
};
