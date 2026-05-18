#pragma once
#include "Shapes.h"
#include "App.h"
#include <cmath>

class PointDistanceRelation : public Relation {
public:
    PointDistanceRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure() const;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTDISTANCE; }
    Storage<double> getParameters() const;
    void setParameters(const Storage<double>& p);
    Storage<double> partitions() const;
};