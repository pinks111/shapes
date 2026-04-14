#pragma once 
#include "Storage.h"
#include "Identi.h"
#include "Shapes.h"


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
    Identi addArrange(MutualArrangeType type, const Storage<Identi>& ii);
    Identi addArrange(MutualArrangeType type, const Storage<Identi>& ii, double value);
    double sumErrors();
	
	bool solve();

    
    Storage<Point<double>>& getPoints() { return pointStorage_; }
    Storage<Segment<double>>& getSegments() { return segmentStorage_; }
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
};
