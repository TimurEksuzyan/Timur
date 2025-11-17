#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
*@brief Расссчитывает силу тяжести и вес мешка
*@param x масса мешка
*@return возвращает рассчитанное значение силы тяжести и вес мешка
*/
double GravityWeight(const double x);
/**
 * @brief считывает значение, 
 * введенное с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getValue();
/**
 * @brief проверяет,что переменная положительная
 * @param value значение проверяемой переменной
 */
void checkValue(const double value);
/*
*@brief Точка входа в программу
*@param x заданный пользователем значение массы мешка
*@param value выдает ошибку, если пользователь ввел неверное значение 
*@return возвращает 0, если программа выполнена корректно
*/
int main()
{
    printf("Введите массу мешка:");
    double x = getValue();
    checkValue(x);
    printf("Сила тяжести и вес мешка = %.2lf Н\n",GravityWeight(x));

}

double getValue()
{
    double value = 0;
    if (!scanf("%lf",&value))
    {
        printf("Error\n");
        abort();
    }
    return value;
}

void checkValue(const double value)
{
    if (value <= 0 + __DBL_EPSILON__)
    {
        printf("Число должно быть положительным\n");
        abort();
    }
}
double GravityWeight(const double x)
{
    return x * 9.8;
}
