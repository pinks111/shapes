#include "Matrix.h"

class Bitmap {
public:
  Bitmap(size_t r, size_t c);
  Bitmap(const char* filename): matrix_(Matrix(0, 0)) {};

  bool Get(size_t r, size_t c);

  void Set(size_t r, size_t c, bool state);

  void Save(const char* filename);

private:
  Matrix matrix_;

};
