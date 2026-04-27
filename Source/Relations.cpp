#include "Relations.h"
#include "App.h"
#include <cmath>

static Storage<double> pointParams(Point<double>* p) {
    Storage<double> r;
    r.addItem(p->x());
    r.addItem(p->y());
    return r;
}

static Storage<double> segmentParams(Segment<double>* s) {
    Storage<double> r;
    r.addItem(s->p1().x());
    r.addItem(s->p1().y());
    r.addItem(s->p2().x());
    r.addItem(s->p2().y());
    return r;
}

// measure

double PointCoincidentRelation::measure() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return 0.0;
    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::sqrt(dx * dx + dy * dy);
}

double PointDistanceRelation::measure() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return 0.0;
    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::abs(std::sqrt(dx * dx + dy * dy) - value_);
}

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

double SegmentsNormalRelation::measure() const {
    Segment<double>* s1 = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    Segment<double>* s2 = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!s1 || !s2) return 0.0;
    double ax = s1->p2().x() - s1->p1().x();
    double ay = s1->p2().y() - s1->p1().y();
    double bx = s2->p2().x() - s2->p1().x();
    double by = s2->p2().y() - s2->p1().y();
    double lenA = std::sqrt(ax * ax + ay * ay);
    double lenB = std::sqrt(bx * bx + by * by);
    if (lenA == 0.0 || lenB == 0.0) return 0.0;
    return std::abs(ax * bx + ay * by) / (lenA * lenB);
}

double SegmentVerticalRelation::measure() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return 0.0;
    return std::abs(seg->p2().x() - seg->p1().x());
}

double SegmentLengthRelation::measure() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return 0.0;
    return std::abs(seg->length() - value_);
}

// getParameters

Storage<double> PointCoincidentRelation::getParameters() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
}

Storage<double> PointDistanceRelation::getParameters() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
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

Storage<double> SegmentsNormalRelation::getParameters() const {
    Segment<double>* s1 = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    Segment<double>* s2 = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!s1 || !s2) return Storage<double>();
    Storage<double> r = segmentParams(s1);
    Storage<double> r2 = segmentParams(s2);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
}

Storage<double> SegmentVerticalRelation::getParameters() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    return segmentParams(seg);
}

Storage<double> SegmentLengthRelation::getParameters() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    return segmentParams(seg);
}

// setParameters

void PointCoincidentRelation::setParameters(const Storage<double>& p) {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return;
    p1->set_x(p.getItem(0)); p1->set_y(p.getItem(1));
    p2->set_x(p.getItem(2)); p2->set_y(p.getItem(3));
}

void PointDistanceRelation::setParameters(const Storage<double>& p) {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return;
    p1->set_x(p.getItem(0)); p1->set_y(p.getItem(1));
    p2->set_x(p.getItem(2)); p2->set_y(p.getItem(3));
}

void PointBelongsToSegmentRelation::setParameters(const Storage<double>& p) {
    Point<double>*   pt  = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Segment<double>* seg = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!pt || !seg) return;
    pt->set_x(p.getItem(0)); pt->set_y(p.getItem(1));
    seg->set_p1(Point<double>(p.getItem(2), p.getItem(3)));
    seg->set_p2(Point<double>(p.getItem(4), p.getItem(5)));
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

void SegmentsNormalRelation::setParameters(const Storage<double>& p) {
    Segment<double>* s1 = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    Segment<double>* s2 = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!s1 || !s2) return;
    s1->set_p1(Point<double>(p.getItem(0), p.getItem(1)));
    s1->set_p2(Point<double>(p.getItem(2), p.getItem(3)));
    s2->set_p1(Point<double>(p.getItem(4), p.getItem(5)));
    s2->set_p2(Point<double>(p.getItem(6), p.getItem(7)));
}

void SegmentVerticalRelation::setParameters(const Storage<double>& p) {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return;
    seg->set_p1(Point<double>(p.getItem(0), p.getItem(1)));
    seg->set_p2(Point<double>(p.getItem(2), p.getItem(3)));
}

void SegmentLengthRelation::setParameters(const Storage<double>& p) {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return;
    seg->set_p1(Point<double>(p.getItem(0), p.getItem(1)));
    seg->set_p2(Point<double>(p.getItem(2), p.getItem(3)));
}

// partitions 

Storage<double> PointCoincidentRelation::partitions() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return Storage<double>();
    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist == 0.0) return Storage<double>();
    Storage<double> result;
    result.addItem( dx / dist);
    result.addItem( dy / dist);
    result.addItem(-dx / dist);
    result.addItem(-dy / dist);
    return result;
}

Storage<double> PointDistanceRelation::partitions() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return Storage<double>();
    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist == 0.0) return Storage<double>();
    double sign = (dist - value_ >= 0.0) ? 1.0 : -1.0;
    Storage<double> result;
    result.addItem( sign * dx / dist);
    result.addItem( sign * dy / dist);
    result.addItem(-sign * dx / dist);
    result.addItem(-sign * dy / dist);
    return result;
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

Storage<double> SegmentsNormalRelation::partitions() const {
    Segment<double>* s1 = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    Segment<double>* s2 = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!s1 || !s2) return Storage<double>();
    double ax = s1->p2().x() - s1->p1().x();
    double ay = s1->p2().y() - s1->p1().y();
    double bx = s2->p2().x() - s2->p1().x();
    double by = s2->p2().y() - s2->p1().y();
    double lenA = std::sqrt(ax * ax + ay * ay);
    double lenB = std::sqrt(bx * bx + by * by);
    if (lenA == 0.0 || lenB == 0.0) return Storage<double>();
    double dot  = ax * bx + ay * by;
    double sign = (dot >= 0.0) ? 1.0 : -1.0;
    double d_dax = sign * (bx / (lenA * lenB) - dot * ax / (lenA * lenA * lenA * lenB));
    double d_day = sign * (by / (lenA * lenB) - dot * ay / (lenA * lenA * lenA * lenB));
    double d_dbx = sign * (ax / (lenA * lenB) - dot * bx / (lenA * lenB * lenB * lenB));
    double d_dby = sign * (ay / (lenA * lenB) - dot * by / (lenA * lenB * lenB * lenB));
    Storage<double> result;
    result.addItem(-d_dax);
    result.addItem(-d_day);
    result.addItem( d_dax);
    result.addItem( d_day);
    result.addItem(-d_dbx);
    result.addItem(-d_dby);
    result.addItem( d_dbx);
    result.addItem( d_dby);
    return result;
}

Storage<double> SegmentVerticalRelation::partitions() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    double dx   = seg->p2().x() - seg->p1().x();
    double sign = (dx >= 0.0) ? 1.0 : -1.0;
    Storage<double> result;
    result.addItem(-sign); 
    result.addItem(0.0);   
    result.addItem(sign); 
    result.addItem(0.0);
    return result;
}

Storage<double> SegmentLengthRelation::partitions() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    double dx  = seg->p2().x() - seg->p1().x();
    double dy  = seg->p2().y() - seg->p1().y();
    double len = std::sqrt(dx * dx + dy * dy);
    if (len < 1e-12) return Storage<double>();
    double sign = (len - value_ >= 0.0) ? 1.0 : -1.0;
    Storage<double> result;
    result.addItem(sign * (-dx / len));
    result.addItem(sign * (-dy / len));
    result.addItem(sign * ( dx / len));
    result.addItem(sign * ( dy / len));
    return result;
}
