#include "camera.h"

Camera::Camera():
	camera_(Point4d<double>(0, 0, 0)),
	focal_point_(Point4d<double>(0, 0, 1)) {
		transform_[0][0] = 1;
		transform_[1][1] = 1;
		transform_[2][2] = 1;
		transform_[3][3] = 1;
	}

Camera& Camera::operator = (const Camera& camera) {
	camera_ = camera.camera_;
	focal_point_ = camera.focal_point_;
	transform_ = camera.transform_;
	return (*this);
}
  	
template <typename T>
sf::Vector2f Camera::projectPoint(Point4d<T> p) {
	p = transform_ * p;
	return {p.x / p.w, p.y / p.w};
}

template <typename T>
Line2d Camera::projectLine(Line4d<T> line) {
	return Line2d(projectPoint(line.start_), projectPoint(line.finish_));
}
void Camera::move_camera(Vector4d v) {
	Matrix4d moving;
	moving[0][0] = 1;
	moving[1][1] = 1;
	moving[2][2] = 1;
	moving[3][3] = 1;
	moving[0][3] = v.x;
	moving[1][3] = v.y;
	moving[2][3] = v.z;
	camera_ = moving * camera_;
	transform_ = moving * transform_;
}
void Camera::rotate_camera(double angle, int fixed_coord) {
	Matrix4d moving;
	moving[fixed_coord][fixed_coord] = 1;
	moving[(fixed_coord + 1) % 3][(fixed_coord + 1) % 3] = std::cos(angle);
	moving[(fixed_coord + 2) % 3][(fixed_coord + 2) % 3] = std::cos(angle);
	moving[(fixed_coord + 1) % 3][(fixed_coord + 2) % 3] = std::sin(angle);
	moving[(fixed_coord + 2) % 3][(fixed_coord + 1) % 3] = -std::sin(angle);
	moving[3][3] = 1;
	camera_ = moving * camera_;
	transform_ = moving * transform_;
}
void Camera::draw_axis(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		projectLine(Line4d<double>(Vector4d(0, 0, 0), AXIS[i])).draw(window, COLORS[i]);
	}
}