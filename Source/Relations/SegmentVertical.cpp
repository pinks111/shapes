#include "Relations/SegmentVertical.h"


double SegmentVerticalRelation::measure() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return 0.0;
    return std::abs(seg->p2().x() - seg->p1().x());
}

Storage<double> SegmentVerticalRelation::getParameters() const {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return Storage<double>();
    return segmentParams(seg);
}

void SegmentVerticalRelation::setParameters(const Storage<double>& p) {
    Segment<double>* seg = app_->findObjectById(objects_.getItem(0), app_->getSegments());
    if (!seg) return;
    seg->set_p1(Point<double>(p.getItem(0), p.getItem(1)));
    seg->set_p2(Point<double>(p.getItem(2), p.getItem(3)));
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
