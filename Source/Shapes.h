#pragma once
#include "Identi.h"
#include "Storage.h"
#include "Rectangle.h"
#include <cmath>
#include <iostream>
#include <algorithm>

enum class PrimitiveType{ POINT, SEGMENT, CIRCLE, RECTANGLE };

enum class MutualArrangeType {
	POINTCOINCIDENT,       // Две точки совпадают
	POINTDISTANCE,         // Две точки на заданном расстоянии
	POINTSSYMMETRYSEGMENT, // Две точки симметричны относительно отрезка
	POINTBELONGSTOSEGMENT, // Точка должна принадлежать отрезку
	SEGMENTSNORMAL,        // Два отрезка ортогональны
	SEGMENTVERTICAL,       // Отрезок должен быть вертикальным
	SEGMENTLENGTH          // Отрезок должен иметь указанную длину
};

class GeometricObject {
protected:
    Identi id_;
    
public:
    GeometricObject() {}
    GeometricObject(const Identi& id) : id_(id) {}
    ~GeometricObject() {}

    Identi getId() const { return id_; }
    void setId(const Identi& id) { id_ = id; }
    
    void print() const {}
};

class App;

class Relation : public GeometricObject {
protected:
    Storage<Identi> objects_;
    double value_;
    App* app_ = nullptr;
    
public:
    Relation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : GeometricObject(id), objects_(objects), value_(value) {}
    
    virtual ~Relation() {}

    void setApp(App* app) { app_ = app; }
    
    const Storage<Identi>& getObjects() const { return objects_; }
    double getValue() const { return value_; }
    
    virtual double measure() const = 0;

    virtual Storage<double> getParameters() const = 0;
	virtual void setParameters(const Storage<double>&) = 0;	
	virtual Storage<double> partitions() const = 0;

    double error() const { return std::abs(measure() - value_);  }
    
    virtual MutualArrangeType getType() const = 0;

    virtual void setTargetValue(double value) { value_ = value; }
    
    void print() const {
        std::cout << "Relation ID: " << id_.getID() 
                  << ", Type: " << static_cast<int>(getType()) + 1
                  << ", Objects: " << objects_.getSize()
                  << ", Value: " << value_ << std::endl;
    }
};

template <typename num> class point_coor {
protected:
    num x_, y_;
public:
    point_coor(num x = 0, num y = 0) : x_(x), y_(y) {}
    num x() const { return x_; }
    num y() const { return y_; }
    void set_x(num x) { x_ = x; }
    void set_y(num y) { y_ = y; }
};

template <typename num> class Point : public GeometricObject, public point_coor<num> {
public:
    Point(num x = 0, num y = 0) : point_coor<num>(x, y) {}

    Identi getId() const { return id_; }
    void setId(const Identi& new_id) { id_ = new_id; }

    Rectangle<num> getBoundingRect() const {
        return Rectangle<num>(
            point_coor<num>(this->x_, this->y_),
            point_coor<num>(this->x_, this->y_)
        );
    }
};

template <typename num>
std::ostream& operator<<(std::ostream& os, const Point<num>& point) {
    os << "Point(ID: " << point.getId().getID() 
       << ", x: " << point.x() 
       << ", y: " << point.y() << ")";
    return os;
}

template <typename num> class Segment : public GeometricObject {
    Point<num> p1_, p2_;
    
public:
    Segment(const Point<num>& p1 = Point<num>(), const Point<num>& p2 = Point<num>()) 
        : p1_(p1), p2_(p2) {}
    
    const Point<num>& p1() const { return p1_; }
    const Point<num>& p2() const { return p2_; }
    void set_p1(const Point<num>& p1) { p1_ = p1; }
    void set_p2(const Point<num>& p2) { p2_ = p2; }
    
    double length() const {
        double dx = p1_.x() - p2_.x();
        double dy = p1_.y() - p2_.y();
        return std::sqrt(dx*dx + dy*dy);  
    }

    Rectangle<num> getBoundingRect() const {
        num min_x = std::min(p1_.x(), p2_.x());
        num min_y = std::min(p1_.y(), p2_.y());
        num max_x = std::max(p1_.x(), p2_.x());
        num max_y = std::max(p1_.y(), p2_.y());
        return Rectangle<num>(
            point_coor<num>(min_x, max_y),
            point_coor<num>(max_x, min_y)
        );
    }
};

template <typename num>
std::ostream& operator<<(std::ostream& os, const Segment<num>& segment) {
    os << "Segment(ID: " << segment.getId().getID() 
       << ", from (" << segment.p1().x() << ", " << segment.p1().y() 
       << ") to (" << segment.p2().x() << ", " << segment.p2().y() << "))";
    return os;
}

template <typename num> class Circle : public GeometricObject {
    Point<num> center_;
    double radius_;
    
public: 
    Circle() : center_(Point<num>(0, 0)), radius_(0.0) {}
    Circle(const Point<num>& center, double radius) 
        : center_(center), radius_(radius) {}
    
    const Point<num>& center() const { return center_; }
    double radius() const { return radius_; }
    void set_center(const Point<num>& center) { center_ = center; }
    void set_radius(double radius) { radius_ = radius; }

    Rectangle<num> getBoundingRect() const {
        return Rectangle<num>(
            point_coor<num>(center_.x() - radius_, center_.y() + radius_),
            point_coor<num>(center_.x() + radius_, center_.y() - radius_)
        );
    }
};

template<typename num>
std::ostream& operator<<(std::ostream& os, const Circle<num>& circle) {
    os << "Circle(ID: " << circle.getId().getID() 
       << ", center: (" << circle.center().x() << ", " << circle.center().y() 
       << "), radius: " << circle.radius() << ")";
    return os;
}
