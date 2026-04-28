#pragma once 
#include "Storage.h"
#include "Identi.h"
#include "Shapes.h"
#include "Rectangle.h"


class App{
    static int count;
    Storage<Point<double>>   pointStorage_;
    Storage<Segment<double>> segmentStorage_;
    Storage<Circle<double>>  circleStorage_;
	Storage<Relation*>       relationStorage_;
    
public:
    App(); 
    ~App();
    
    Identi addObject(PrimitiveType type);
    Identi addPoint(double x, double y);
    Identi addSegment(double x1, double y1, double x2, double y2);
    Identi addCircle(double cx, double cy, double radius);
    Identi addArrange(MutualArrangeType type, const Storage<Identi>& ii);
    Identi addArrange(MutualArrangeType type, const Storage<Identi>& ii, double value);
    double sumErrors();
	
	bool solve();

    Rect<double> unionRect() const;

    // масштабирует размер и возвращает итоговый размер в outW/outH.
    void scaleToFit(size_t& outW, size_t& outH);

    
    Storage<Point<double>>& getPoints() { return pointStorage_; }
    Storage<Segment<double>>& getSegments() { return segmentStorage_; }
    Storage<Circle<double>>& getCircles() { return circleStorage_; }
    const Storage<Point<double>>& getPoints() const { return pointStorage_; }
    const Storage<Segment<double>>& getSegments() const { return segmentStorage_; }
    const Storage<Circle<double>>& getCircles() const { return circleStorage_; }

    template<typename T> 
    T* findObjectById(const Identi& id, Storage<T>& storage) {
        for(size_t i = 0; i < storage.getSize(); ++i) {
            if(storage.getItem(i).getId() == id) {
                return &storage.getItem(i);
            }
        }
        return nullptr;
    }

    template<typename T>
    const T* findObjectById(const Identi& id, const Storage<T>& storage) const {
        for(size_t i = 0; i < storage.getSize(); ++i) {
            if(storage.getItem(i).getId() == id) {
                return &storage.getItem(i);
            }
        }
        return nullptr;
    }
};
