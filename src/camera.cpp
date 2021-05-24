#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(double max_x, double max_y): kScreenHeight_(max_y), kScreenWidth_(max_x) {}

void Camera::create_transformation_matrixes() {
    Matrix4d canonical_to_screen{
        kScreenWidth_ / 2, 0,     0, kScreenWidth_ / 2 - 0.5,
        0,     kScreenHeight_ / 2, 0, kScreenHeight_ / 2 - 0.5,
        0,     0,     1,     0,
        0,     0,     0,     1,};
    Matrix4d rect_to_canonical{
        2.0 / (kRightPoint_.x - kLeftPoint_.x), 0, 0, 0,
        0, 2.0 / (kRightPoint_.y - kLeftPoint_.y), 0, 0,
        0, 0, 2.0 / (kRightPoint_.z - kLeftPoint_.z), 0,
        0, 0, 0, 1};
    Matrix4d move_to_center{
        1, 0, 0, - (kLeftPoint_.x + kRightPoint_.x) / 2.0,
        0, 1, 0, - (kLeftPoint_.y + kRightPoint_.y) / 2.0,
        0, 0, 1, - (kLeftPoint_.z + kRightPoint_.z) / 2.0,
        0, 0, 0, 1};
    Matrix4d projective_transform{
        kLeftPoint_.z, 0, 0, 0,
        0, kLeftPoint_.z, 0, 0,
        0, 0, kLeftPoint_.z + kRightPoint_.z, -kLeftPoint_.z * kRightPoint_.z,
        0, 0, 1, 0};
    Matrix4d move_camera{
        1, 0, 0, -position_.x / position_.w,
        0, 1, 0, -position_.y / position_.w,
        0, 0, 1, -position_.z / position_.w,
        0, 0, 0, 1};
    transform_space_to_screen_ = canonical_to_screen * rect_to_canonical  *  move_to_center * projective_transform;
    transform_to_camera_space_ = camera_rotation_.transpose() * move_camera;
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    camera_rotation_ = camera_rotation_ * matrix;
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
    return transform_space_to_screen_ * p;
}

sf::Vector2f Camera::project_point(Point4d p) const {
    Point4d transformed = transform_point(p);
    return {transformed.x / transformed.w,
            transformed.y / transformed.w};
}

double Camera::get_z_value(Point4d p) const {
    return transform_point(p).z / transform_point(p).w;
}

Point4d Camera::to_cameras_coordinates(Point4d p) const {
    return transform_to_camera_space_ * p;
}

double Camera::get_clipping_plane() const {
    return kClipPlane_;
}

}
