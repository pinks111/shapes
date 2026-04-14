#include "Relations.h"
#include "App.h"
#include <cmath>


double PointCoincidentRelation::measure(App& app) const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double>* p1 = app.findObjectById(id1, app.getPoints());
    Point<double>* p2 = app.findObjectById(id2, app.getPoints());
    if (p1 == nullptr || p2 == nullptr) {
        return 0.0;
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::sqrt(dx * dx + dy * dy);
}

Storage<double> PointCoincidentRelation::partitions(App& app) const {
	Identi id1 = objects_.getItem(0);
	Identi id2 = objects_.getItem(1);

	Point<double>* p1 = app.findObjectById(id1, app.getPoints());
	Point<double>* p2 = app.findObjectById(id2, app.getPoints());
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

double PointDistanceRelation::measure(App& app) const {
    Identi id1 = objects_.getItem(0);
    Identi id2 = objects_.getItem(1);

    Point<double>* p1 = app.findObjectById(id1, app.getPoints());
    Point<double>* p2 = app.findObjectById(id2, app.getPoints());
    if (p1 == nullptr || p2 == nullptr) {
        return 0.0;
    }

    double dx = p1->x() - p2->x();
    double dy = p1->y() - p2->y();
    return std::sqrt(dx * dx + dy * dy);
}

double PointBelongsToSegmentRelation::measure(App& app) const {
    return 0.0;
}

double SegmentVerticalRelation::measure(App& app) const {
    Identi segmentId = objects_.getItem(0);

    Segment<double>* seg = app.findObjectById(segmentId, app.getSegments());
    if (seg == nullptr) {
        return 0.0;
    }

    double dx = seg->p2().x() - seg->p1().x();
    return std::abs(dx);
}

double PointsSymmetrySegmentRelation::measure(App& app) const {
    return 0.0;    
}


double SegmentsNormalRelation::measure(App& app) const {
    return 0.0;
}


double SegmentLengthRelation::measure(App& app) const {
    return 0.0;
}
