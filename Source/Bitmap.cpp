#include "Bitmap.h"

Bitmap::Bitmap(size_t r, size_t c) {
	matrix_ = Matrix(r, c);
}
Bitmap::Bitmap(const char* filename);

~Bitmap() {
	delete matrix_;
}

bool Bitmap::Get(size_t r, size_t c);

void Bitmap::Set(size_t r, size_t c, bool state);

void Bitmap::Save(const char* filename);