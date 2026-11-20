#include "Task2.h"

miit::algebra::Task2::Task2(const size_t r, const size_t c, Generator& gen)
    : Exercise(r, c, gen)
{
}

void miit::algebra::Task2::solve()
{
    size_t r = matrix.getRows();
    if (r == 0 || matrix.getCols() == 0) return;

    for (size_t j = matrix.getCols(); j > 0; --j)
    {
        size_t col_index = j - 1;
        if (matrix[0][col_index] > matrix[r - 1][col_index])
        {
            matrix.removeColumn(col_index);
        }
    }
}