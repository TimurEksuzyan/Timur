#include "Task1.h"
#include <cstdlib>

miit::algebra::Task1::Task1(const size_t r, const size_t c, Generator& gen) 
    : Exercise(r, c, gen)
{
}

void miit::algebra::Task1::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    for (size_t j = 0; j < c; ++j)
    {
        size_t min_row = 0;
        int min_abs = std::abs(matrix[0][j]);

        for (size_t i = 1; i < r; ++i)
        {
            int current_abs = std::abs(matrix[i][j]);
            if (current_abs < min_abs)
            {
                min_abs = current_abs;
                min_row = i;
            }
        }

        matrix[min_row][j] = 0;
    }
}