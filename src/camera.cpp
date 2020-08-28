#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(Renderer* renderer): renderer_(renderer) {
    assert(renderer);
}

void Camera::apply_transform_to_camera(const Matrix4d& matrix) {
    position_ = matrix * position_;
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    basis_screen_ = matrix * basis_screen_;
    basis_world_ = matrix * basis_world_;
}

void Camera::create_transform() {
    transform_ = basis_screen_ * basis_screen_.transpose();
}

Matrix4d Camera::get_world_transform() const {
    return basis_world_;
}

double Camera::get_max_z_value() const {
    return kMaxDistance_ + 1;
}

double Camera::get_focus_distance() const {
    return kFocusDistance_;
}

Point4d Camera::transform_point(Point4d p) const {
    p = p - position_;
    Vector4d proj = transform_ * p;
    Vector4d ort = p - proj;
    Matrix<2, 1> res = basis_screen_.transpose() * Matrix<4, 1>(proj);
    p.x = res(0, 0);
    p.y = res(1, 0);
    p.z = ort.length();
    p.w = 1;
    return p;
}

sf::Vector2f Camera::project_point(Point4d p) const {
    p = transform_point(p);
    if (p.z >= kMinDistance_ && p.z <= kMaxDistance_) {
        return {p.x, p.y};
    }
    return kDefaultPixel_;
}

double Camera::get_z_value(Point4d p) const {
    p = transform_point(p);
    if (p.z >= kMinDistance_ && p.z <= kMaxDistance_) {
        return p.z;
    }
    return get_max_z_value();
}

}
