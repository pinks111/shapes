#pragma once 

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
	// Метод для добавления примитивов 
	Identi addObject(PrimitiveType type);

	// Метод для добавления пожеланий о расположении
        addArrange(MutualArrangeType type,  Storage<Identi> ii)
      	// Метод для добавления пожеланий о расположении с дополнительным параметром
	addArrange(MutualArrangeType type,  Storage<Identi> ii, double value)


private:

    Storage<Point<double>>   pointStorage_;

    Storage<Segment<double>> segmentStorage_;
    Storage<Circle<double>>  circleStorage_;

    // Метод для оценки взаимного расположения объектов
    double measure_(MutualArrangeType type,  Storage<Identi> ii);

};