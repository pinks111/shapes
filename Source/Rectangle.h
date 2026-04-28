#pragma once
#include <algorithm>

template <typename num> class point_coor {
protected:
    num x_, y_;
public:
    point_coor(num x = 0, num y = 0) : x_(x), y_(y) {}
    num x() const { return x_; }
    num y() const { return y_; }
    void set_x(num x) { x_ = x; }
    void set_y(num y) { y_ = y; }
};

template <typename num> class Rect {
    point_coor<num> top_left_;
    point_coor<num> bottom_right_;

public:
    Rect(
        const point_coor<num>& top_left     = point_coor<num>(),
        const point_coor<num>& bottom_right = point_coor<num>())
        : top_left_(top_left), bottom_right_(bottom_right) {}

    const point_coor<num>& topLeft()     const { return top_left_; }
    const point_coor<num>& bottomRight() const { return bottom_right_; }

    void setTopLeft(const point_coor<num>& p)     { top_left_     = p; }
    void setBottomRight(const point_coor<num>& p) { bottom_right_ = p; }

    num width()  const { return bottom_right_.x() - top_left_.x(); }
    num height() const { return top_left_.y() - bottom_right_.y(); }

    Rect<num> unite(const Rect<num>& other) const {
        return Rect<num>(
            point_coor<num>(std::min(top_left_.x(),     other.top_left_.x()),
                            std::max(top_left_.y(),     other.top_left_.y())),
            point_coor<num>(std::max(bottom_right_.x(), other.bottom_right_.x()),
                            std::min(bottom_right_.y(), other.bottom_right_.y()))
        );
    }
};
