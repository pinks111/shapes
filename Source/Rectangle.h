#pragma once
#include "Shapes.h"

template <typename num> class Rectangle {
    point_coor<num> top_left_;
    point_coor<num> bottom_right_;

public:
    Rectangle(
        const point_coor<num>& top_left     = point_coor<num>(),
        const point_coor<num>& bottom_right = point_coor<num>())
        : top_left_(top_left), bottom_right_(bottom_right) {}

    const point_coor<num>& topLeft()     const { return top_left_; }
    const point_coor<num>& bottomRight() const { return bottom_right_; }

    void setTopLeft(const point_coor<num>& p)     { top_left_     = p; }
    void setBottomRight(const point_coor<num>& p) { bottom_right_ = p; }

};
