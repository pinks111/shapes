#include <stddef.h>

class Matrix {
    bool **array_;
    size_t cols_;
    size_t rows_;
public:
    Matrix(size_t height, size_t width): rows_(height), cols_(width)
    {
        array_ = new bool*[height];
        for (int i = 0; i < height; i++)
        {
            array_[i] = new bool[width];
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < rows_; i++)
        {
            delete[] array_[i];
        }
        delete[] array_;
    }

    bool get(size_t row, size_t col);
};
