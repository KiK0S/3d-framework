#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(Screen* screen): screen_(screen) {
    assert(screen);
}

void Camera::apply_transform_to_camera(const Matrix4d& matrix) {
    position_ = matrix * position_;
}

void Camera::apply_transform_to_world(const Matrix4d& matrix) {
    basis_screen_ = matrix * basis_screen_;
    basis_world_ = matrix * basis_world_;
}

void Camera::create_transform() {
    Matrix<2, 2> id = Matrix<2, 2>::identity_matrix();
    transform_ = basis_screen_ * basis_screen_.transpose();
}

Matrix4d Camera::find_inverse_transform() const {
    return basis_world_.inverse();
}

Point4d Camera::transform_point(Point4d p) const {
    p = p - position_;
    Vector4d proj = transform_ * p;
    Vector4d ort = p - proj;
    Matrix<4, 1> kek;
    kek(0, 0) = proj.x;
    kek(1, 0) = proj.y;
    kek(2, 0) = proj.z;
    kek(3, 0) = proj.w;
    Matrix<2, 1> res = basis_screen_.transpose() * kek;
    p.x = res(0, 0);
    p.y = res(1, 0);
    p.z = ort.length();
    p.w = 1;
    return p;
}

sf::Vector2f Camera::project_point(Point4d p) const {
    p = transform_point(p);
    if (p.z >= kMinDistance && p.z <= kMaxDistance) {
        return {p.x, p.y};
    }
    return kDefaultPixel;
}

double Camera::get_z_value(Point4d p) const {
    p = transform_point(p);
    if (p.z >= kMinDistance && p.z <= kMaxDistance) {
        return p.z;
    }
    return kMaxDistance;
}

}
