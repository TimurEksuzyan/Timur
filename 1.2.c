#include <stdio.h>
#include <math.h>

/**
 * @brief рассчитывает площадь грани куба
 * @param side ребро куба
 * @return возвращает рассчитанный Плоцадь
 */
double getFaceArea(const double side);

/**
 * @brief рассчитывает площадь полной поверхности куба
 * @param side ребро куба
 * @return возвращает рассчитанный Площадь
 */
double getTotalSurfaceArea(const double side);

/**
 * @brief рассчитывает объём куба
 * @param side ребро куба
 * @return возвращает рассчитанный объём
 */
double getVolume(const double side);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
    double side;
    printf("Ведите значение:");
    scanf("%lf",&side);
    printf("Сторона равна %.2lf\n", side);
    printf("Площадь ребра равна %.2lf",getFaceArea(side));
    printf("Площадь полной поверхности равна %.2lf",getTotalSurfaceArea(side));
    printf("Объём равен %.2lf",getVolume(side));
    return 0;
}

double getFaceArea(const double side)
{
    return side * side;
}

double getTotalSurfaceArea(const double side)
{
    return 6 * pow(side,2);
}

double getVolume(const double side)
{
    return pow(side,3);

}
