#include <iostream>
#include <gtest/gtest.h>
#include "../Source/Matrix.h"


#include "../Source/App.h"
#include "../Source/Relations.h"
#include <cmath>

TEST(PointDistance, SamePoint) {
    App app;
    Identi p1 = app.addObject(PrimitiveType::POINT);

    Point<double>* point = app.findObjectById(p1, app.getPoints());
    point->set_x(0);
    point->set_y(0);
    
    Storage<Identi> ids;
    ids.addItem(p1);
    ids.addItem(p1);
    
    PointDistanceRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 0.0);
}

TEST(PointDistance, DifferentPoints) {
    App app;
    Identi p1 = app.addObject(PrimitiveType::POINT);
    Identi p2 = app.addObject(PrimitiveType::POINT);

    Point<double>* point1 = app.findObjectById(p1, app.getPoints());
    Point<double>* point2 = app.findObjectById(p2, app.getPoints());
    point1->set_x(-1);
    point1->set_y(-1);
    point2->set_x(2);
    point2->set_y(3);

    Storage<Identi> ids;
    ids.addItem(p1);
    ids.addItem(p2);

    PointDistanceRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 5.0);
}

TEST(PointCoincident, SamePoint) {
    App app;
    Identi p1 = app.addObject(PrimitiveType::POINT);

    Point<double>* point = app.findObjectById(p1, app.getPoints());
    point->set_x(0);
    point->set_y(0);
    
    Storage<Identi> ids;
    ids.addItem(p1);
    ids.addItem(p1);
    
    PointCoincidentRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 0.0);
}

TEST(PointCoincident, DifferentPoints) {
    App app;
    Identi p1 = app.addObject(PrimitiveType::POINT);
    Identi p2 = app.addObject(PrimitiveType::POINT);

    Point<double>* point1 = app.findObjectById(p1, app.getPoints());
    Point<double>* point2 = app.findObjectById(p2, app.getPoints());
    point1->set_x(1);
    point1->set_y(2);
    point2->set_x(4);
    point2->set_y(6);
    
    Storage<Identi> ids;
    ids.addItem(p1);
    ids.addItem(p2);
    
    PointCoincidentRelation relation(Identi(), ids);
    relation.setApp(&app);
    double distance = relation.measure();
    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(SegmentVertical, VerticalSegment) {
    App app;
    Identi s1 = app.addObject(PrimitiveType::SEGMENT);

    Segment<double>* segment = app.findObjectById(s1, app.getSegments());
    segment->set_p1(Point<double>(2, 0));
    segment->set_p2(Point<double>(2, 5));

    Storage<Identi> ids;
    ids.addItem(s1);

    SegmentVerticalRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 0.0);
}

TEST(SegmentVertical, NonVerticalSegment) {
    App app;
    Identi s1 = app.addObject(PrimitiveType::SEGMENT);

    Segment<double>* segment = app.findObjectById(s1, app.getSegments());
    segment->set_p1(Point<double>(0, 0));
    segment->set_p2(Point<double>(4, 0));

    Storage<Identi> ids;
    ids.addItem(s1);

    SegmentVerticalRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 4.0);
}

TEST(SegmentVertical, NegativeDirection) {
    App app;
    Identi s1 = app.addObject(PrimitiveType::SEGMENT);

    Segment<double>* segment = app.findObjectById(s1, app.getSegments());
    segment->set_p1(Point<double>(3, 1));
    segment->set_p2(Point<double>(-2, 7));

    Storage<Identi> ids;
    ids.addItem(s1);

    SegmentVerticalRelation relation(Identi(), ids);
    relation.setApp(&app);
    EXPECT_DOUBLE_EQ(relation.measure(), 5.0);
}
