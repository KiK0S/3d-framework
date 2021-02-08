#include "camera.h"
#include "log.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(Renderer* renderer): renderer_(renderer) {
    assert(renderer);
}

void Camera::move_camera(const Matrix4d& matrix) {
    // position_ = matrix * position_;
    eye = matrix * eye;
}

void Camera::rotate_camera(const Matrix4d& matrix) {
    // basis_screen_ = matrix * basis_screen_;
    // basis_world_ = matrix * basis_world_;
    eye = matrix * eye;
    up = matrix * up;
    gaze = matrix * gaze;
    left = matrix * left;
    up /= up.length();
    left /= left.length();
    gaze /= gaze.length();

}

void Camera::create_transform() {
    Matrix4d move = get_move();
    Matrix4d rotate = get_rotate();
    debug(rotate);
    debug(move);
    transform_ = rotate * move;
    debug(transform_);
}

Matrix4d Camera::get_move() const {
    return Matrix4d({
        {1, 0, 0, -eye.x},
        {0, 1, 0, -eye.y},
        {0, 0, 1, -eye.z},
        {0, 0, 0, 1}
    });
}

Matrix4d Camera::get_rotate() const {

    return Matrix4d ({
        {up.x, up.y, up.z, 0},
        {left.x, left.y, left.z, 0},
        {gaze.x, gaze.y, gaze.z, 0},
        {0, 0, 0, 1}
    });
}

Matrix4d Camera::get_world_transform() const {
    return basis_world_;
}

double Camera::get_max_z_value() const {
    return kMaxDistance_ - kFocusDistance_;
}

double Camera::get_min_z_value() const {
    return kMinDistance_ - kFocusDistance_;
}

double Camera::get_focus_distance() const {
    return kFocusDistance_;
}

Point4d Camera::transform_point(Point4d p) const {

    // debug("projecting");
    // debug(transform_);
    // debug(p);
    Vector4d proj = transform_ * p;
    // debug(proj);
    // debug("~~~\n");
    return {proj.x / proj.w, proj.y / proj.w, proj.z / proj.w};
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
    return {p.x, p.y};
}

double Camera::get_z_value(Point4d p) const {
    p = transform_point(p);
    return p.z;
}

}
