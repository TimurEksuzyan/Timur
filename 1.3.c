#include <stdio.h>
#include <math.h>
/*
*@brief Расссчитывает силу тяжести и вес мешка
*@param x масса мешка
*@return возвращает рассчитанное значение силы тяжести и вес мешка
*/
double GravityWeight(const double x);
/*
*@brief Точка входа в программу
*@param x заданный пользователем значение массы мешка
*@param value выдает ошибку, если пользователь ввел неверное значение 
*@return возвращает 0, если программа выполнена корректно
*/
int main()
{
    double x;
    int value;
    printf("Введите массу мешка:");
    value = scanf("%lf",&x);
    if (value == 1)
    {
        if (x > 0)
        {
            printf("Сила тяжести и вес мешка = %.2lf Н\n",GravityWeight(x));
        }
        else
        {
            printf("Неверное значение\n");
        }
    }
    else
    {
        printf("Неверное значение\n");
    }
    return 0;
}
double GravityWeight(const double x)
{
    return x * 9.8;
}
