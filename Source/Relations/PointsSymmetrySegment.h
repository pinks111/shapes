#pragma once 
#include "Shapes.h"
#include "App.h"

class PointsSymmetrySegmentRelation : public Relation {
public:
    PointsSymmetrySegmentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const {
        return 0.0;    
    }
    MutualArrangeType getType() const override { return MutualArrangeType::POINTSSYMMETRYSEGMENT; }
};