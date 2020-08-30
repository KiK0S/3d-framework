#include "log.h"
#include "point.h"
#include "triangle.h"

namespace app {

Triangle4d::Triangle4d(Point4d a, Point4d b, Point4d c): a(a), b(b), c(c) {}

void Triangle4d::sort_points(std::array<int, 3> order, Point4d& a, Point4d& b, Point4d& c) const {
    if (order[0] == 0) {
        a = this->a;
    }
    if (order[0] == 1) {
        a = this->b;
    }
    if (order[0] == 2) {
        a = this->c;
    }
    if (order[1] == 0) {
        b = this->a;
    }
    if (order[1] == 1) {
        b = this->b;
    }
    if (order[1] == 2) {
        b = this->c;
    }
    if (order[2] == 0) {
        c = this->a;
    }
    if (order[2] == 1) {
        c = this->b;
    }
    if (order[2] == 2) {
        c = this->c;
    }
}

Triangle2d::Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c): a(a), b(b), c(c) {
    if (a.x > b.x) {
        std::swap(a, b);
    }
    if (a.x > c.x) {
        std::swap(a, c);
    }
    if (b.x > c.x) {
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
    if (a.x <= b.x && a.x <= c.x) {
        return a;
    }
    if (c.x <= b.x && c.x <= a.x) {
        return c;
    }
    return b;
}

sf::Vector2f Triangle2d::get_right_point() const {
    if (a.x >= b.x && a.x >= c.x) {
        return a;
    }
    if (c.x >= b.x && c.x >= a.x) {
        return c;
    }
    return b;
}

Matrix<2, 2> Triangle2d::create_basis() const {
    if (a == get_left_point()) {
        return Matrix<2, 2> ({b - a, c - a}).transpose();
    }
    if (b == get_left_point()) {
        return Matrix<2, 2> ({a - b, c - b}).transpose();
    }
    if (c == get_left_point()) {
        return Matrix<2, 2> ({a - c, b - c}).transpose();
    }
    return Matrix<2, 2>();
}

/*
    the same order as in create_basis()
*/
std::array<int, 3> Triangle2d::get_order() const {
    if (a == get_left_point()) {
        return {0, 1, 2};
    }
    if (b == get_left_point()) {
        return {1, 0, 2};
    }
    if (c == get_left_point()) {
        return {2, 0, 1};
    } 
    return {0, 1, 2};
}

double Triangle2d::square() const {
    return 0.5 * cross(b - a, c - a);
}

}
