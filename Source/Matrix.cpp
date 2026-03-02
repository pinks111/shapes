#include "Matrix.h"

Matrix::Matrix(size_t height, size_t width) : rows_(height), cols_(width)
{
    array_ = new bool* [height];
    for (int i = 0; i < height; i++)
    {
        array_[i] = new bool[width];
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

bool Matrix::get(size_t row, size_t col);
