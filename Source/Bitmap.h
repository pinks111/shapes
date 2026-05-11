#pragma once 
#include <fstream>
#include <cstdint>
#include "Matrix.h"
#include "../Storages-shapes/Storage/Storage.h"

class Bitmap {
public:
  Bitmap(size_t r, size_t c): matrix_(r, c) {}

  bool Get(size_t r, size_t c);

  void Set(size_t r, size_t c, bool state) {
    matrix_.set(r, c, state);
  }

  size_t GetWidth() const { return matrix_.cols(); }
  size_t GetHeight() const { return matrix_.rows(); }

  void Save(const char* filename);
  void Load(const char *filename);

private:
	Matrix matrix_;
};
