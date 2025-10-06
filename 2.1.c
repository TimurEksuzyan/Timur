#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief рассчитывает периметр прямоугольного треугольника
 * @param side1 первая сторона треугольника
 * @param side2 вторая сторона треугольника
 * @return возвращает рассчитанный Периметр
 */
double getPerimetr(const double side1, const double side2);

/**
 * @brief рассчитывает площадь прямоугольного треугольника
 * @param side1 первая сторона треугольника
 * @param side2 вторая сторона треугольника
 * @return возвращает рассчитанный Площадь
 */
double getSquare(const double side1, const double side2);

/**
 * @brief perimetr - периметр треугольника
 * @brief ploshad - площадь треугольника
 */
enum{perimetr,ploshad};

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

/**
 * @brief Точка входа в программу
 * @param side1 первая сторона треугольника
 * @param side2 вторая сторона треугольника
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
    printf("Введите стороны треугольника: ");
    double side1 = getValue();
    checkValue(side1);
    double side2 = getValue();
    checkValue(side2);
    printf("Выберите что хотите посчитать: %d - периметр, %d - площадь\n",perimetr,ploshad);
    int choise = (int) getValue();
    switch (choise)
    {
        case perimetr:
            printf("Периметр равен %.21f\n",getPerimetr(side1,side2));
            break;
        case ploshad:
            printf("Площадь равена %.21f\n",getSquare(side1,side2));
            break;
        default:
            printf("Неверное значение");
            abort();
    }

    return 0;
}

double getPerimetr(const double side1, const double side2)
{
    return sqrt((side1 * side1) + (side2 * side2))+(side1+side2);
}

double getSquare(const double side1, const double side2)
{
    return (side1 * side2) / 2;
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
