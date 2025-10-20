#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
/*
*@brief Рассчитывает значение функции по заданным условиям
*@param x входное значение аргумента
*@return возвращает рассчитанное значение выбранной функции
*/
double func(const double x);
/*
*@brief Считывает значение, введенное с клавиатуру с проверкой ввода
*@return считанное значение
*/
double value();
/*
*@brief Точка входа в программу
*@param x выбранный пользователем значение аргумента
*@return Возвращает 0, если программа выполнена корректно
*/
int main()
{
    printf("Введите значение:");
    double x = value();
    double result = func(x);
    printf("Результат: y(%.2f) = %.2f\n", x, result);
    return 0;
    
}

double func(const double x)
{
    const double a = 2.0;
    
    if (x <= 1.0 + DBL_EPSILON)
    {
        
        return 1.0;
    }
    else if (x >= 1.0 - DBL_EPSILON && x <= 2.0 + DBL_EPSILON)
    {
        
        return a * pow(x, 2.0 * log(x));
    }
    else 
    {
        
        return exp(a * x) * cos(x);
    }
}

double value()
{
    double value = 0;
    if (!scanf("%lf",&value))
    {
        printf("Ошибка! Введено неверное значение!\n");

        abort();
    }
    return value;

}
