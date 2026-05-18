#include <iostream>
#include <string>
#include <cmath>
#include "ForwardDerivativeSolver.h"
#include "CentralDerivativeSolver.h"

/**
 * @brief Пример функции: f(x) = x^2
 * Производная f'(x) = 2x. В точке x=5 результат должен быть около 10.
 */
double myFunc(double x)
{
    return x * x;
}

double getValue(std::string report)
{
    std::cout << report;
    double value = 0;
    std::cin >> value;
    return value;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    double x = getValue("Введите точку x, в которой ищем производную: ");
    double h = getValue("Введите шаг h (например, 0.0001): ");

    ForwardDerivativeSolver forward;
    CentralDerivativeSolver central;

    double res1 = forward.solve(x, 0, h, myFunc);
    double res2 = central.solve(x, 0, h, myFunc);

    std::cout << "Правая разностная производная: " << res1 << std::endl;
    std::cout << "Центральная разностная производная: " << res2 << std::endl;

    return 0;
}
