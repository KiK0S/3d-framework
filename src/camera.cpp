#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera() {}

void Camera::create_transform() {
    Matrix4d canonical2Screen{
        kScreenSize_ / 2, 0,     0, kScreenSize_ / 2 - 0.5,
        0,     kScreenSize_ / 2, 0, kScreenSize_ / 2 - 0.5,
        0,     0,     1,     0,
        0,     0,     0,     1,};
    Matrix4d rect2Canonical{
        2.0 / (kRightPoint_.x - kLeftPoint_.x), 0, 0, 0,
        0, 2.0 / (kRightPoint_.y - kLeftPoint_.y), 0, 0,
        0, 0, 2.0 / (kRightPoint_.z - kLeftPoint_.z), 0,
        0, 0, 0, 1};
    Matrix4d move2Center{
        1, 0, 0, - (kLeftPoint_.x + kRightPoint_.x) / 2.0,
        0, 1, 0, - (kLeftPoint_.y + kRightPoint_.y) / 2.0,
        0, 0, 1, - (kLeftPoint_.z + kRightPoint_.z) / 2.0,
        0, 0, 0, 1};
    Matrix4d move_camera{
        1, 0, 0, -position_.x / position_.w,
        0, 1, 0, -position_.y / position_.w,
        0, 0, 1, -position_.z / position_.w,
        0, 0, 0, 1};
    transform_ = canonical2Screen * rect2Canonical  *  move2Center; // * magic * transform_camera_.transpose() * move_camera;
    debug(transform_);
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    transform_camera_ = transform_camera_ * matrix;
}

Matrix4d Camera::get_world_transform() const {
    return transform_;
}

double Camera::get_max_z_value() const {
    return kRightPoint_.z;
}

double Camera::get_min_z_value() const {
    return kLeftPoint_.z;
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

Point4d Camera::to_cameras_coordinates(Point4d p) const {
    Matrix4d move_camera{
        1, 0, 0, -position_.x / position_.w,
        0, 1, 0, -position_.y / position_.w,
        0, 0, 1, -position_.z / position_.w,
        0, 0, 0, 1};
    Matrix4d magic{
        kLeftPoint_.z, 0, 0, 0,
        0, kLeftPoint_.z, 0, 0,
        0, 0, kLeftPoint_.z + kRightPoint_.z, -kLeftPoint_.z * kRightPoint_.z,
        0, 0, 1, 0};
        debug(magic);
    debug(magic * transform_camera_.transpose() * move_camera);
    return magic * transform_camera_.transpose() * move_camera * p;
}


}
