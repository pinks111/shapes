#include "Relations/SegmentLength.h"


double SegmentLengthRelation::measure() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return 0.0;
    return std::abs(seg->length() - value_);
}

Storage<double> SegmentLengthRelation::getParameters() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    return segmentParams(seg);
}

void SegmentLengthRelation::setParameters(const Storage<double>& p) {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return;
    seg->set_p1(Point<double>(p.getItem(0), p.getItem(1)));
    seg->set_p2(Point<double>(p.getItem(2), p.getItem(3)));
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
