#include "PointCoincident.h"


double PointCoincidentRelation::measure() const {
        Identi id1 = objects_.getItem(0);
        Identi id2 = objects_.getItem(1);

        Point<double>* p1 = app_->findObjectById(id1, app_->getPoints());
        Point<double>* p2 = app_->findObjectById(id2, app_->getPoints());
        if (p1 == nullptr || p2 == nullptr) {
            return 0.0;
        }

        double dx = p1->x() - p2->x();
        double dy = p1->y() - p2->y();
        return std::sqrt(dx * dx + dy * dy);
}

Storage<double> PointCoincidentRelation::partitions() const {
        Identi id1 = objects_.getItem(0);
        Identi id2 = objects_.getItem(1);

        Point<double>* p1 = app_->findObjectById(id1, app_->getPoints());
        Point<double>* p2 = app_->findObjectById(id2, app_->getPoints());
        if (p1 == nullptr || p2 == nullptr) {
            return 0.0;
        }

        double dx = p1->x() - p2->x();
        double dy = p1->y() - p2->y();


        Storage<double> result;

        result.addItem(dx / std::sqrt(dx * dx + dy * dy));
        result.addItem(dy / std::sqrt(dx * dx + dy * dy));
        result.addItem(-dx / std::sqrt(dx * dx + dy * dy));
        result.addItem(-dy / std::sqrt(dx * dx + dy * dy));
        return result;
}

Storage<double> PointCoincidentRelation::getParameters() const {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return Storage<double>();
    Storage<double> r = pointParams(p1);
    Storage<double> r2 = pointParams(p2);
    for (size_t i = 0; i < r2.getSize(); ++i) r.addItem(r2.getItem(i));
    return r;
}

void PointCoincidentRelation::setParameters(const Storage<double>& p) {
    Point<double>* p1 = app_->findObjectById(objects_.getItem(0), app_->getPoints());
    Point<double>* p2 = app_->findObjectById(objects_.getItem(1), app_->getPoints());
    if (!p1 || !p2) return;
    p1->set_x(p.getItem(0)); p1->set_y(p.getItem(1));
    p2->set_x(p.getItem(2)); p2->set_y(p.getItem(3));
}

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
