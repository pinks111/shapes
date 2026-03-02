#include "Bitmap.h"

Bitmap(size_t r, size_t c) {
	matrix_ = Matrix(r, c);
}
Bitmap(const char* filename);

~Bitmap() {
	delete matrix_;
}

bool Get(size_t r, size_t c);

void Set(size_t r, size_t c, bool state);

void Save(const char* filename);