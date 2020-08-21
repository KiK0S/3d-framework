#include "camera.h"
#include "matrix.h"
#include <cassert>

namespace app {

Camera::Camera(Screen* screen): screen_(screen) {
    assert(screen);
}

void Camera::apply_matrix(const Matrix4d& matrix) {
    camera_ = matrix * camera_;
    transform_ = matrix * transform_;
}

Matrix4d Camera::find_inverse_transform() const {
    return transform_.inverse();
}

sf::Vector2f Camera::project_point(Point4d p) const {
    p = transform_ * p;
    if (p.z / p.w + screen_->kScreenSize / 2 > MIN_Z && p.z / p.w + screen_->kScreenSize / 2 < MAX_Z) {
        return {p.x / p.w, p.y / p.w};
    }
    return {0, 0};
}

double Camera::get_z_value(Point4d p) const {
    p = transform_ * p;
    if (p.z / p.w + screen_->kScreenSize / 2 > MIN_Z && p.z / p.w + screen_->kScreenSize / 2 < MAX_Z) {
        return p.z / p.w;
    }
    return screen_->kScreenSize * 10;
}

}
