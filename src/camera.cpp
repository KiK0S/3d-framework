#include "camera.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(double screen_width, double screen_height):
    kScreenHeight_(screen_height),
    kScreenWidth_(screen_width) {}

Point4d Camera::transform_to_cameras_coordinates(const Point4d& p) const {
    return transform_to_camera_space_ * p;
}

Point4d Camera::transform_to_screen(const Point4d& p) const {
    Point4d result = transform_space_to_screen_ * p;
    result.normalize();
    return result;
}

sf::Vector2f Camera::project_on_screen(const Point4d& p) const {
    Point4d transformed = transform_to_screen(p);
    return {transformed.x, transformed.y};
}

double Camera::get_z_value(const Point4d& p) const {
    Point4d transformed = transform_to_screen(p);
    return transformed.z;
}

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
        1, 0, 0, -focus_point_.x / focus_point_.w,
        0, 1, 0, -focus_point_.y / focus_point_.w,
        0, 0, 1, -focus_point_.z / focus_point_.w,
        0, 0, 0, 1};
    transform_space_to_screen_ = canonical_to_screen *
                                 rect_to_canonical  *
                                 move_to_center *
                                 projective_transform;
    transform_to_camera_space_ = camera_rotation_.transpose() * move_camera;
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    camera_rotation_ *= matrix;
}

double Camera::get_max_z_value() const {
    return kRightPoint_.z;
}

double Camera::get_min_z_value() const {
    return kLeftPoint_.z;
}

void Camera::move(const Point4d& v) {
    Point4d m = v;
    focus_point_ -= m;
}

double Camera::get_clipping_plane_distance() const {
    return kClippingPlaneDistance_;
}

}
