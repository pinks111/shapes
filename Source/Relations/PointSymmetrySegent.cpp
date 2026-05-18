#include "Relations/PointsSymmetrySegment.h"

double PointsSymmetrySegmentRelation::measure() const {
    Point<double>*   p1  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>*   p2  = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(2), app_->getSegments());
    if (!p1 || !p2 || !seg) return 0.0;
    double mx = (p1->x() + p2->x()) / 2.0;
    double my = (p1->y() + p2->y()) / 2.0;
    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = mx - seg->p1().x();
    double by = my - seg->p1().y();
    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) return std::sqrt(bx * bx + by * by);
    return std::abs(ax * by - ay * bx) / len;
}

Storage<double> PointsSymmetrySegmentRelation::getParameters() const {
    Point<double>*   p1  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>*   p2  = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(2), app_->getSegments());
    if (!p1 || !p2 || !seg) return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    Storage<double> r3 = segmentParams(seg);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    for (size_t i = 0; i < r3.getSize(); ++i) r.addItem(r3.getItem(i));
    return r;
}

void PointsSymmetrySegmentRelation::setParameters(const Storage<double>& p) {
    Point<double>*   p1  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>*   p2  = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(2), app_->getSegments());
    if (!p1 || !p2 || !seg) return;
    p1->set_x(p.getItem(0)); p1->set_y(p.getItem(1));
    p2->set_x(p.getItem(2)); p2->set_y(p.getItem(3));
    seg->set_p1(Point<double>(p.getItem(4), p.getItem(5)));
    seg->set_p2(Point<double>(p.getItem(6), p.getItem(7)));
}

Storage<double> PointsSymmetrySegmentRelation::partitions() const {
    Point<double>*   p1  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>*   p2  = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(2), app_->getSegments());
    if (!p1 || !p2 || !seg) return Storage<double>();
    double mx = (p1->x() + p2->x()) / 2.0;
    double my = (p1->y() + p2->y()) / 2.0;
    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = mx - seg->p1().x();
    double by = my - seg->p1().y();
    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) return Storage<double>();
    double cross = ax * by - ay * bx;
    double sign  = (cross >= 0.0) ? 1.0 : -1.0;
    Storage<double> result;
    result.addItem(sign * (-ay) / len * 0.5);
    result.addItem(sign * ( ax) / len * 0.5);
    result.addItem(sign * (-ay) / len * 0.5);
    result.addItem(sign * ( ax) / len * 0.5);
    result.addItem(sign * ( ay) / len);
    result.addItem(sign * (-ax) / len);
    result.addItem(sign * (-ay) / len);
    result.addItem(sign * ( ax) / len);
    return result;
}
