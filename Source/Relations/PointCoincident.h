#pragma once
#include "Shapes.h"
#include "App.h"
#include <cmath>


class PointCoincidentRelation : public Relation {
public:
    PointCoincidentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure() const;
    
    Storage<double> partitions() const;
    
    MutualArrangeType getType() const override { return MutualArrangeType::POINTCOINCIDENT; }

    Storage<double> getParameters() const;
    void setParameters(const Storage<double>& p);
    Storage<double> partitions() const;
};