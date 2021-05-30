#include "point.h"
#include "triangle.h"

namespace app {

Triangle4d::Triangle4d(Point4d a, Point4d b, Point4d c): a(a), b(b), c(c) {}

void Triangle4d::get_points(std::array<int, 3> order, Point4d *a, Point4d *b, Point4d *c) const {
    std::vector<Point4d> points = {
        this->a, this->b, this->c
    };
    *a = points[order[0]];
    *b = points[order[1]];
    *c = points[order[2]];
}

Triangle2d::Triangle2d(sf::Vector2f _a, sf::Vector2f _b, sf::Vector2f _c): a(_a), b(_b), c(_c) {
    for (int i = 0; i < 3; i++) {
        order_[i] = i;
    }
    if (a.x > b.x || (a.x == b.x && a.y > b.y)) {
        std::swap(order_[0], order_[1]);
        std::swap(a, b);
    }
    if (a.x > c.x || (a.x == c.x && a.y > c.y)) {
        std::swap(a, c);
        std::swap(order_[0], order_[2]);
    }
    if (cross(b - a, c - a) < 0) {
        std::swap(order_[1], order_[2]);
        std::swap(b, c);
    }
    // like for handle sorting 3 elements
}

bool Triangle2d::inner_point(const sf::Vector2f& o) const {
    bool f1 = cross(o - a, b - a) >= 0;
    bool f2 = cross(o - b, c - b) >= 0;
    bool f3 = cross(o - c, a - c) >= 0;
    bool s1 = cross(o - a, b - a) <= 0;
    bool s2 = cross(o - b, c - b) <= 0;
    bool s3 = cross(o - c, a - c) <= 0;
    return f1 && f2 && f3 || s1 && s2 && s3;
}

sf::Vector2f Triangle2d::get_left_point() const {
    return a;
}

sf::Vector2f Triangle2d::get_right_point() const {
    sf::Vector2f ans = a;
    if (ans.x < b.x || ans.x == b.x && ans.y < b.y) {
        ans = b;
    }
    if (ans.x < c.x || ans.x == c.x && ans.y < c.y) {
        ans = c;
    }
    return ans;
}

Matrix<2, 2> Triangle2d::create_basis() const {
    return Matrix<2, 2> ({b - a, c - a}).transpose();
}

/*
    the same order as in create_basis()
*/
std::array<int, 3> Triangle2d::get_order() const {
    return order_;
}

double Triangle2d::square() const {
    return 0.5 * cross(b - a, c - a);
}

double Triangle2d::min_y_in_line(double x) const {
    if (std::abs(b.x - x) < 1e-10) {
        return b.y;
    }
    if (b.x > x) {
        sf::Vector2f v = a - b;
        if (std::abs(v.x) < 1e-5) {
            return a.y;
        }
        double k = (b.x - x) / v.x;
        v *= std::abs(k);
        return (b + v).y;
    }
    else {
        sf::Vector2f v = c - b;
        if (std::abs(v.x) < 1e-5) {
            return b.y;
        }
        double k = (b.x - x) / v.x;
        v *= std::abs(k);
        return (b + v).y;
    }
}

double Triangle2d::max_y_in_line(double x) const {
    if (std::abs(c.x - x) < 1e-10) {
        return c.y;
    }
    if (c.x > x) {
        sf::Vector2f v = a - c;
        if (std::abs(v.x) < 1e-5) {
            return c.y;
        }
        double k = (c.x - x) / v.x;
        v *= std::abs(k);
        return (c + v).y;
    }
    else {
        sf::Vector2f v = b - c;
        if (std::abs(v.x) < 1e-5) {
            return c.y;
        }
        double k = (c.x - x) / v.x;
        v *= std::abs(k);
        return (c + v).y;
    }
}

bool Triangle2d::is_degenerate() const {
    return a == b || a == c || b == c;
}

}
