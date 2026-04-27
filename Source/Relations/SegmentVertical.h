#pragma once
#include "Shapes.h"
#include "App.h"
#include <cmath>

class SegmentVerticalRelation : public Relation {
public:
    SegmentVerticalRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const {
        Identi segmentId = objects_.getItem(0);

        Segment<double>* seg = app.findObjectById(segmentId, app.getSegments());
        if (seg == nullptr) {
            return 0.0;
        }

        double dx = seg->p2().x() - seg->p1().x();
        return std::abs(dx);
    }
    MutualArrangeType getType() const override { return MutualArrangeType::SEGMENTVERTICAL; }
};
