#define _USE_MATH_DEFINES // for C
#include <math.h>
#include <stdio.h>

/**
 * @brief Рассчитывает функцию В по заданной формуле
 * @param x - значение параметра x
 * @param y - значение параметра y
 * @param z - значение параметра z
 * @return рассчитанное значение
 */
double getB(const double x, const double y, const double z);

/**
 * @brief Рассчитывает функцию A по заданной формуле
 * @param x - значение параметра x
 * @param y - значение параметра y
 * @param z - значение параметра z
 * @return рассчитанное значение
 */
double getA(const double x, const double y, const double z);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main()
{
    const double x = 0.78;
    const double y = 1.24;
    const double z = 0.5;
    printf("A = %lf", getA(x, y, z));
    printf("B = %lf", getB(x, y, z));
    return 0;
}

double getB(const double x, const double y, const double z)
{
    return x * exp(sqrt(z)) * cos((x * x) / (y * z));
}

double getA(const double x, const double y, const double z)
{
    return (2 * pow(z,x)) / (sqrt(pow(y,x) * pow(cos(x + y),2)) - 3 * z);
}