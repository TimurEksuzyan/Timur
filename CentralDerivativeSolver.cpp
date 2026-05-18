#include "CentralDerivativeSolver.h"
#include <iostream>
#include <cstdlib>

double CentralDerivativeSolver::solve(const double x, const double unused, const double h, double (*f)(double)) const
{
    if (h <= 0)
    {
        std::cout << "Ошибка. Шаг h должен быть положительным.\n";
        exit(1);
    }
    return (f(x + h) - f(x - h)) / (2.0 * h);
}
