#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera() {}

void Camera::create_transform() {
    Vector4d vector_add = default_position_ - position_;
    Matrix4d transform_move = Matrix4d::identity_matrix();
    transform_move(0, 3) = vector_add[0] / vector_add[3];
    transform_move(1, 3) = vector_add[1] / vector_add[3];
    transform_move(2, 3) = vector_add[2] / vector_add[3];
    transform_ = transform_camera_ * transform_move;
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    transform_camera_ *= matrix;
}

Matrix4d Camera::get_world_transform() const {
    return transform_;
}

double Camera::get_max_z_value() const {
    return 1000000000;
}

double Camera::get_min_z_value() const {
    return -1000000000;
}

double Camera::get_focus_distance() const {
    return 0; 
}

void Camera::move(Point4d v) {
    Matrix<1, 4> m = Matrix<4,1>(v).transpose() * transform_camera_.inverse();
    position_ -= Vector4d(m(0, 0) / m(0, 3), m(0, 1) / m(0, 3), m(0, 2) / m(0, 3));
}

Point4d Camera::transform_point(Point4d p) const {
    return transform_ * p;
}

sf::Vector2f Camera::project_point(Point4d p) const {
    debug("===");
    transform_.print();
    debug("===");
    return {transform_point(p).x / transform_point(p).w, 
            transform_point(p).y / transform_point(p).w};
}

double Camera::get_z_value(Point4d p) const {
    return transform_point(p).z / transform_point(p).w;
}

}
