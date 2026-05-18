#include "Relations/PointDistance.h"

double PointDistanceRelation::measure() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return 0.0;
    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::abs(std::sqrt(dx * dx + dy * dy) - value_);
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

void PointDistanceRelation::setParameters(const Storage<double>& p) {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return;
    p1->set_x(p.getItem(0)); p1->set_y(p.getItem(1));
    p2->set_x(p.getItem(2)); p2->set_y(p.getItem(3));
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
