#pragma once
#include "Shapes.h"
#include "App.h"
#include <cmath>

class PointDistanceRelation : public Relation {
public:
    PointDistanceRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const {
        Identi id1 = objects_.getItem(0);
        Identi id2 = objects_.getItem(1);

        Point<double>* p1 = app.findObjectById(id1, app.getPoints());
        Point<double>* p2 = app.findObjectById(id2, app.getPoints());
        if (p1 == nullptr || p2 == nullptr) {
            return 0.0;
        }

        double dx = p1->x() - p2->x();
        double dy = p1->y() - p2->y();
        return std::sqrt(dx * dx + dy * dy);
    }
    MutualArrangeType getType() const override { return MutualArrangeType::POINTDISTANCE; }
};