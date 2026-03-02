#include <stddef.h>
#include <Matrix.h>

struct IndexError
{
    char *log;
};


class Matrix {
    bool **array_;
    size_t cols_;
    size_t rows_;
    const static IndexError indexError_ = IndexError{"Index out of range"};
    void checkIndexes_(size_t row, size_t col) const
    {
        if (row > rows_-1 || col > cols_-1)
            throw indexError_;
    }
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
    bool get(size_t row, size_t col) const
    {
        checkIndexes_(row, col);
        return array_[row][col];
    }
    void set(size_t row, size_t col, bool state)
    {
        checkIndexes_(row, col);
        array_[row][col] = state;
    }
};