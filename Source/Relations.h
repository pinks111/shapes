#pragma once
#include "Shapes.h"

class PointCoincidentRelation : public Relation {
public:
    PointCoincidentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTCOINCIDENT; }
};

class PointDistanceRelation : public Relation {
public:
    PointDistanceRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTDISTANCE; }
};

class PointsSymmetrySegmentRelation : public Relation {
public:
    PointsSymmetrySegmentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTSSYMMETRYSEGMENT; }
};

class PointBelongsToSegmentRelation : public Relation {
public:
    PointBelongsToSegmentRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::POINTBELONGSTOSEGMENT; }
};

class SegmentsNormalRelation : public Relation {
public:
    SegmentsNormalRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::SEGMENTSNORMAL; }
};

class SegmentVerticalRelation : public Relation {
public:
    SegmentVerticalRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::SEGMENTVERTICAL; }
};

// Это требование заданной длины отрезка
class SegmentLengthRelation : public Relation {
public:
    SegmentLengthRelation(const Identi& id, const Storage<Identi>& objects, double value = 0.0)
        : Relation(id, objects, value) {}
    double measure(App& app) const override;
	Storage<double> partitions(App& app) const override;
    MutualArrangeType getType() const override { return MutualArrangeType::SEGMENTLENGTH; }
};
