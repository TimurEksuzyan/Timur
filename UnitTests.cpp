#include <iostream>
#include <cassert>
#include <cmath>
#include <limits> 
#include "ForwardDerivativeSolver.h"
#include "CentralDerivativeSolver.h"

/**
 * @brief Тестовая функция f(x) = x^3. 
 * Аналитическая производная f'(x) = 3x^2.
 */
double testFunc1(double x) {
    return x * x * x;
}

void runTests() {
    ForwardDerivativeSolver forward;
    CentralDerivativeSolver central;
    
    const double EPS = std::numeric_limits<double>::epsilon() * 1e10; 
    
    double h = 1e-7; 
    double x1 = 2.0;
    double expected1 = 12.0;

    double resForward = forward.solve(x1, 0, h, testFunc1);
    double resCentral = central.solve(x1, 0, h, testFunc1);

    assert(std::abs(resForward - expected1) < EPS);
    assert(std::abs(resCentral - expected1) < EPS);

    std::cout << "Тесты пройдены с использованием std::numeric_limits!" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    runTests();
    return 0;
}
