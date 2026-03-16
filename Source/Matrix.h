#pragma once
#include <cstddef>

class Matrix {
    bool **array_;
    size_t cols_;
    size_t rows_;
    void checkIndexes_(size_t row, size_t col) const;

public:
    Matrix(size_t rows, size_t cols);

    ~Matrix();

    bool get(size_t row, size_t col) const;

    void set(size_t row, size_t col, bool state);
};
