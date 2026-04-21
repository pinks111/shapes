#include "Relations.h"
#include "App.h"
#include <cmath>

double PointCoincidentRelation::measure() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double> *p1 = app_->findObjectById(id1, app_->getPoints());
    Point<double> *p2 = app_->findObjectById(id2, app_->getPoints());
    if (p1 == nullptr || p2 == nullptr)
    {
        return 0.0;
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::sqrt(dx * dx + dy * dy);
}

Storage<double> PointCoincidentRelation::partitions() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double> *p1 = app_->findObjectById(id1, app_->getPoints());
    Point<double> *p2 = app_->findObjectById(id2, app_->getPoints());
    if (p1 == nullptr || p2 == nullptr) {
        return Storage<double>();
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    double dist = std::sqrt(dx * dx + dy * dy);

    Storage<double> result;
    result.addItem(dx / dist);
    result.addItem(dy / dist);
    result.addItem(-dx / dist);
    result.addItem(-dy / dist);
    return result;
}

double PointDistanceRelation::measure() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double> *p1 = app_->findObjectById(id1, app_->getPoints());
    Point<double> *p2 = app_->findObjectById(id2, app_->getPoints());
    if (p1 == nullptr || p2 == nullptr) {
        return 0.0;
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    double current_dist = std::sqrt(dx * dx + dy * dy);
    return std::abs(current_dist - value_);
}

Storage<double> PointDistanceRelation::partitions() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double> *p1 = app_->findObjectById(id1, app_->getPoints());
    Point<double> *p2 = app_->findObjectById(id2, app_->getPoints());
    if (p1 == nullptr || p2 == nullptr) {
        return Storage<double>();
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist == 0.0) {
        return Storage<double>();
    }

    Storage<double> result;
    result.addItem(dx / dist);
    result.addItem(dy / dist);
    result.addItem(-dx / dist);
    result.addItem(-dy / dist);
    return result;
}

double PointBelongsToSegmentRelation::measure() const {
    Identi ptId = objects_.getItem(0);
    Identi segId = objects_.getItem(1);

    Point<double> *pt = app_->findObjectById(ptId, app_->getPoints());
    Segment<double> *seg = app_->findObjectById(segId, app_->getSegments());
    if (pt == nullptr || seg == nullptr) {
        return 0.0;
    }

    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = pt->x() - seg->p1().x();
    double by = pt->y() - seg->p1().y();

    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) {
        return std::sqrt(bx * bx + by * by);
    }
    return std::abs(ax * by - ay * bx) / len;
}

double PointsSymmetrySegmentRelation::measure() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);
    Identi segId = objects_.getItem(2);

    Point<double> *p1 = app_->findObjectById(id1, app_->getPoints());
    Point<double> *p2 = app_->findObjectById(id2, app_->getPoints());
    Segment<double> *seg = app_->findObjectById(segId, app_->getSegments());
    if (p1 == nullptr || p2 == nullptr || seg == nullptr) {
        return 0.0;
    }

    double mx = (p1->x() + p2->x()) / 2.0;
    double my = (p1->y() + p2->y()) / 2.0;

    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = mx - seg->p1().x();
    double by = my - seg->p1().y();

    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) {
        return std::sqrt(bx * bx + by * by);
    }
    return std::abs(ax * by - ay * bx) / len;
}

double SegmentsNormalRelation::measure() const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Segment<double> *s1 = app_->findObjectById(id1, app_->getSegments());
    Segment<double> *s2 = app_->findObjectById(id2, app_->getSegments());
    if (s1 == nullptr || s2 == nullptr) {
        return 0.0;
    }

    double ax = s1->p2().x() - s1->p1().x();
    double ay = s1->p2().y() - s1->p1().y();
    double bx = s2->p2().x() - s2->p1().x();
    double by = s2->p2().y() - s2->p1().y();

    double lenA = std::sqrt(ax * ax + ay * ay);
    double lenB = std::sqrt(bx * bx + by * by);
    if (lenA == 0.0 || lenB == 0.0) {
        return 0.0;
    }
    return std::abs(ax * bx + ay * by) / (lenA * lenB);
}

double SegmentVerticalRelation::measure() const {
    Identi segmentId = objects_.getItem(0);

    Segment<double> *seg = app_->findObjectById(segmentId, app_->getSegments());
    if (seg == nullptr) {
        return 0.0;
    }

    double dx = seg->p2().x() - seg->p1().x();
    return std::abs(dx);
}

double SegmentLengthRelation::measure() const {
    Identi segmentId = objects_.getItem(0);

    Segment<double> *seg = app_->findObjectById(segmentId, app_->getSegments());
    if (seg == nullptr) {
        return 0.0;
    }

    return std::abs(seg->length() - value_);
}

Storage<double> PointBelongsToSegmentRelation::partitions() const {
    return Storage<double>();
}

Storage<double> PointsSymmetrySegmentRelation::partitions() const {
    return Storage<double>();
}

Storage<double> SegmentsNormalRelation::partitions() const {
    return Storage<double>();
}

Storage<double> SegmentVerticalRelation::partitions() const {
    return Storage<double>();
}

Storage<double> SegmentLengthRelation::partitions() const {
    return Storage<double>();
}

static Storage<double> pointParams(Point<double> *p) {
    Storage<double> r;
    r.addItem(p->x());
    r.addItem(p->y());
    return r;
}

static Storage<double> segmentParams(Segment<double> *s) {
    Storage<double> r;
    r.addItem(s->p1().x());
    r.addItem(s->p1().y());
    r.addItem(s->p2().x());
    r.addItem(s->p2().y());
    return r;
}

Storage<double> PointCoincidentRelation::getParameters() const {
    Point<double> *p1 =
        app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double> *p2 =
        app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2)
        return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    for (size_t i = 0; i < r2.getSize(); ++i)
        r.addItem(r2.getItem(i));
    return r;
}

Storage<double> PointDistanceRelation::getParameters() const {
    Point<double> *p1 =
        app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double> *p2 =
        app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2)
        return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    for (size_t i = 0; i < r2.getSize(); ++i)
        r.addItem(r2.getItem(i));
    return r;
}

Storage<double> PointsSymmetrySegmentRelation::getParameters() const {
    return Storage<double>();
}

Storage<double> PointBelongsToSegmentRelation::getParameters() const {
    return Storage<double>();
}

Storage<double> SegmentsNormalRelation::getParameters() const {
    return Storage<double>();
}

Storage<double> SegmentVerticalRelation::getParameters() const {
    return Storage<double>();
}

Storage<double> SegmentLengthRelation::getParameters() const {
    return Storage<double>();
}
