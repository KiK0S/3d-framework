#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera() {}

void Camera::create_transform() {
    // Point4d pl = position_ + basis_screen_.row(0) * -1000 + basis_screen_.row(1) * -1000 + basis_screen_.row(2) * -1000;
    // Point4d pr = position_ + basis_screen_.row(0) * 1000 + basis_screen_.row(1) * 1000 + basis_screen_.row(2) * 1000;
    double l = -1000;
    double r = 1000;
    double b = -1000;
    double t = 1000;
    double n = -1000;
    double f = 1000;
    Matrix4d canonical2Screen{
        500.0, 0,     0, 499.5,
        0,     500.0, 0, 499.5,
        0,     0,     1,     0,
        0,     0,     0,     1,};
    Matrix4d rect2Canonical{
        2.0 / (r - l), 0, 0, 0,
        0, 2.0 / (t - b), 0, 0,
        0, 0, 2.0 / (n - f), 0,
        0, 0, 0, 1};
    Matrix4d move2Center{
        1, 0, 0, - (l + r) / 2.0,
        0, 1, 0, - (b + t) / 2.0,
        0, 0, 1, - (n + f) / 2.0,
        0, 0, 0, 1};
    Matrix4d magic{
        n, 0, 0, 0,
        0, n, 0, 0,
        0, 0, n + f, -n * f,
        0, 0, 1, 0};
    Matrix4d move_camera{
        1, 0, 0, -position_.x / position_.w,
        0, 1, 0, -position_.y / position_.w,
        0, 0, 1, -position_.z / position_.w,
        0, 0, 0, 1};
    transform_ = canonical2Screen * rect2Canonical  *  move2Center * magic * transform_camera_.transpose() * move_camera;
    debug(transform_);
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    basis_screen_ = (matrix * basis_screen_.transpose()).transpose();
    transform_camera_ = transform_camera_ * matrix;
}

Matrix4d Camera::get_world_transform() const {
    return transform_;
}

double Camera::get_max_z_value() const {
    return 1000;
}

double Camera::get_min_z_value() const {
    return -1000;
}

void Camera::move(Point4d v) {
    Matrix<1, 4> m = Matrix<4,1>(v).transpose();
    position_ -= Vector4d(m(0, 0) / m(0, 3), m(0, 1) / m(0, 3), m(0, 2) / m(0, 3));
}

Point4d Camera::transform_point(Point4d p) const {
    return transform_ * p;
}

sf::Vector2f Camera::project_point(Point4d p) const {
    Point4d transformed = transform_point(p);
    // debug("===");
    // debug(transformed[0]);
    // debug("===");
    return {transformed.x / transformed.w, 
            transformed.y / transformed.w};
}

double Camera::get_z_value(Point4d p) const {
    return transform_point(p).z / transform_point(p).w;
}

}
