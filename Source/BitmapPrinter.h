#pragma once
#include "Shapes.h"
#include "Bitmap.h"

class BitmapPrinter
{
public:
	BitmapPrinter(size_t width, size_t height);
	~BitmapPrinter();

	void drawPoint(const Point<double>&);
	void drawSegment(const Segment<double>&);
	void drawCircle(const Circle<double>&);
	void save2File(const char* fileName);
private:
	Bitmap * bitmap_;
};

