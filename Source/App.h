#pragma once 
#include "Storage.h"
#include "Identi.h"
#include "Shapes.h"

enum class PrimitiveType{
	POINT,
	SEGMENT,
	CIRCLE
};

enum class MutualArrangeType {
	POINTCOINCIDENT, // Две точки совпадают
	POINTDISTANCE, // Две точки на заданном расстоянии
	POINTSSYMMETRYSEGMENT,  // Две точки симметричны относительно отрезка      
	POINTOBELONGSEGMENT,
	SEGMENTSNORMAL, // Два отрезка ортогональны
	SEGMENTVERTICAL,
	SEGMENTLENGTH
};


class App{
public:
	App();
	// Метод для добавления графических примитивов 
	Identi addObject(PrimitiveType type);

	// Метод для добавления пожеланий о расположении
	void addArrange(MutualArrangeType type, Storage<Identi> ii);
      	// Метод для добавления пожеланий о расположении с дополнительным параметром
	void addArrange(MutualArrangeType type, Storage<Identi> ii, double value);


private:

    Storage<Point<double>>   pointStorage_;

    Storage<Segment<double>> segmentStorage_;
    Storage<Circle<double>>  circleStorage_;

    // Метод для оценки текущего положения дел для неоторого ограничения
    double measure_(MutualArrangeType type,  Storage<Identi> ii);

};