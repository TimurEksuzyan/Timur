#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


/**
 * @brief Получение целочисленного значения от пользователя
 * @return Введенное значение
 */
int Value();

/**
 * @brief Получение размера массива
 * @param message сообщение пользователю
 * @return Размер массива
 */
size_t getSize(char* message);

/**
 * @brief Выделение динамической памяти под массив
 * @param size Размер массива
 * @return Указатель на выделенную память
 */
int* allocateArray(const size_t size);

/**
 * @brief Заполнение массива с клавиатуры
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillArray(int* arr, const size_t size);

/**
 * @brief Заполнение массива случайными числами в указанном диапазоне
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillRandom(int* arr, const size_t size);

/**
 * @brief Вывод массива на экран
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void printArray(const int* arr, const size_t size);

/**
 * @brief Нахождение произведения четных элементов массива
 * @param arr Указатель на массив
 * @param size Размер массива
 * @return Произведение четных элементов или 0, если нет четных элементов
 */
int PolElements(const int* arr, const size_t size);

/**
 * @brief Замена элементов с нечетными индексами на квадраты их индексов
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void Odd(int* arr, const size_t size);

/**
 * @brief Проверка наличия положительных элементов, делящихся на k с остатком 2
 * @param arr Указатель на массив
 * @param size Размер массива
 * @param k Делитель
 * @return true - если есть такие элементы, false - если нет
 */
int Positive(const int* arr, const size_t size, const int k);

/**
 * @brief Выделение динамической памяти под массив целых чисел
 * @param size Размер массива
 * @return Указатель на выделенную память
 */
int* allocateArray(const size_t size);

/**
 * @brief RANDOM - заполнение массива случайными числами
 * @brief MANUAL - заполнение массива вручную.
 */
    enum { RANDOM = 1, MANUAL };

/**
 * @brief Точка входа в программу.
 * @return 0, если программа выполнена корректно.
 */
int main()
{
    srand(time(NULL));

    size_t size = getSize("Введите размер массива:");

    int* arr = allocateArray(size);

    printf("Выберите способ заполнения массива:\n"
        "%d - случайными числами\n"
        "%d - вручную \n", RANDOM, MANUAL);
    int choice = Value();

    switch (choice)
    {
    case RANDOM:
        fillRandom(arr, size);
        break;
    case MANUAL:
        fillArray(arr, size);
        break;
    default:
        printf("Ошибка!\n");
        free(arr);
        exit(1);
    }

    printf("Исходный массив: ");
    printArray(arr, size);

    PolElements(arr, size);


    Odd(arr, size);

    printf("\n2. Массив после замены элементов с нечетными индексами: ");
    printArray(arr, size);

    printf("\n3. Введите число k: ");
    int k = Value();

    Positive(arr, size, k);

    free(arr);
    return 0;
}

int* allocateArray(const size_t size)
{
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    return arr;
}

int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        printf("Ошибка ввода!\n");
        abort();
    }
    return value;
}

size_t getSize(char* message)
{
    printf("%s", message);
    int value = Value();
    if (value <= 0)
    {
        printf("Ошибка: размер массива должен быть положительным!\n");
        abort();
    }
    return value;
}

void fillArray(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("Введите элемент [%zu]: ", i);
        arr[i] = Value();
    }
}

void fillRandom(int* arr, const size_t size)
{
    printf("Введите минимальное значение диапазона: ");
    int min = Value();

    printf("Введите максимальное значение диапазона: ");
    int max = Value();

    if (min > max)
    {
        printf("Минимальное значение больше максимального! Меняю значения местами.\n");
        int temp = min;
        min = max;
        max = temp;
        printf("Новый диапазон: [%d, %d]\n", min, max);
    }

    int range = max - min + 1;

    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % range) + min;
    }

    printf("Массив заполнен случайными числами в диапазоне [%d, %d]\n", min, max);
}

void printArray(const int* arr, const size_t size)
{
    printf("[");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

int PolElements(const int* arr, const size_t size)
{
    int product = 1;
    bool found = false;

    printf("1. Четные элементы массива: ");
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0 && arr[i] != 0)
        {
            printf("%d ", arr[i]);
            found = true;
        }
    }

    if (!found)
    {
        printf("Нет четных элементов\n");
        return 0;
    }

    printf("\n   Произведение четных элементов: ");
    found = false;

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            if (!found)
            {
                printf("%d", arr[i]);
                product = arr[i];
                found = true;
            }
            else
            {
                printf(" * %d", arr[i]);
                product = product * arr[i];
            }
        }
    }

    printf(" = %d\n", product);


    if (product != 0)
    {
        printf("   Результат произведения: %d\n", product);
    }
}

void Odd(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (i % 2 == 1)
        {
            arr[i] = i * i;
        }
    }
}

int Positive(const int* arr, const size_t size, const int k)
{
    int PositiveFound = 0;
    if (k == 0)
    {
        printf("Ошибка: деление на ноль\n");
        abort();
    }

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] > 0 && arr[i] % k == 2)
        {
            PositiveFound = 1;
        }
    }


    if (PositiveFound)
    {
        printf("Есть положительные элементы, делящиеся на %d с остатком 2\n", k);
    }
    else
    {
        printf("Нет положительных элементов, делящихся на %d с остатком 2\n", k);
    }
}