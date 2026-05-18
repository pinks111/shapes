#include "Relations/SegmentNormal.h"


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

Storage<double> SegmentsNormalRelation::getParameters() const {
    Segment<double>* s1 = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    Segment<double>* s2 = app_->findObjectById(objects_.getItem(1), app_->getSegments());
    if (!s1 || !s2) return Storage<double>();
    Storage<double> r = segmentParams(s1);
    Storage<double> r2 = segmentParams(s2);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
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
