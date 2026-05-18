#pragma once
#include "Shapes.h"
#include "App.h"

class PointBelongsToSegmentRelation : public Relation {
public:
    PointBelongsToSegmentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure() const;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTBELONGSTOSEGMENT; }
    Storage<double> getParameters() const;
    void setParameters(const Storage<double>& p);
    Storage<double> partitions() const;
};