#pragma once
#include "Solver.h"

/**
 * @brief Класс для вычисления правой разностной производной
 */
class ForwardDerivativeSolver : public Solver
{
public:
    double solve(const double x, const double unused, const double h, double (*f)(double)) const override;
};
