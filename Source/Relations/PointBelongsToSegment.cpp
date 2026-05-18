#include "Relations/PointBelongsToSegment.h"

double PointBelongsToSegmentRelation::measure() const {
    Point<double>*   pt  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!pt || !seg) return 0.0;
    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = pt->x() - seg->p1().x();
    double by = pt->y() - seg->p1().y();
    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) return std::sqrt(bx * bx + by * by);
    return std::abs(ax * by - ay * bx) / len;
}

Storage<double> PointBelongsToSegmentRelation::getParameters() const {
    Point<double>*   pt  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!pt || !seg) return Storage<double>();
    Storage<double> r = pointParams(pt);
    Storage<double> r2 = segmentParams(seg);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
}

void PointBelongsToSegmentRelation::setParameters(const Storage<double>& p) {
    Point<double>*   pt  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!pt || !seg) return;
    pt->set_x(p.getItem(0)); pt->set_y(p.getItem(1));
    seg->set_p1(Point<double>(p.getItem(2), p.getItem(3)));
    seg->set_p2(Point<double>(p.getItem(4), p.getItem(5)));
}

Storage<double> PointBelongsToSegmentRelation::partitions() const {
    Point<double>*   pt  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!pt || !seg) return Storage<double>();
    double ax = seg->p2().x() - seg->p1().x();
    double ay = seg->p2().y() - seg->p1().y();
    double bx = pt->x() - seg->p1().x();
    double by = pt->y() - seg->p1().y();
    double len = std::sqrt(ax * ax + ay * ay);
    if (len == 0.0) return Storage<double>();
    double cross = ax * by - ay * bx;
    double sign  = (cross >= 0.0) ? 1.0 : -1.0;
    Storage<double> result;
    result.addItem(sign * (-ay) / len);
    result.addItem(sign * ( ax) / len);
    result.addItem(sign * ( ay) / len);
    result.addItem(sign * (-ax) / len);
    result.addItem(sign * (-ay) / len);
    result.addItem(sign * ( ax) / len);
    return result;
}
