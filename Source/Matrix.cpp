#include "Matrix.h"
#include <stdexcept>

void Matrix::checkIndexes_(size_t row, size_t col) const
    {
        if (row > rows_-1 || col > cols_-1)
            throw std::out_of_range("Index out of range");
    }

Matrix::Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols)
{
    array_ = new bool*[rows];
    for (int i = 0; i < rows; i++)
    {
        array_[i] = new bool[cols];
    }
}
Matrix::~Matrix()
{
    for (int i = 0; i < rows_; i++)
    {
        delete[] array_[i];
    }
    delete[] array_;
}
bool Matrix::get(size_t row, size_t col) const
{
    checkIndexes_(row, col);
    return array_[row][col];
}
void Matrix::set(size_t row, size_t col, bool state)
{
    checkIndexes_(row, col);
    array_[row][col] = state;
}
