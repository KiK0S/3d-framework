#pragma once

#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include <SFML/Graphics.hpp>
#include "../matrix/matrix.cpp"
#include <cmath>

class Camera {
  public:
  	Camera():
  		camera_(Point4d<double>(0, 0, 0)),
  		focal_point_(Point4d<double>(0, 0, 1)) {
  			transform_[0][0] = 1;
  			transform_[1][1] = 1;
  			transform_[2][2] = 1;
  			transform_[3][3] = 1;
  		}
  	Camera& operator = (const Camera& camera) {
  		camera_ = camera.camera_;
  		focal_point_ = camera.focal_point_;
  		transform_ = camera.transform_;
  		return (*this);
  	}
  	
  	template <typename T>
  	sf::Vector2f projectPoint(Point4d<T> p) {
		p = transform_ * p;
		return {p.x / p.w, p.y / p.w};
  	}

	template <typename T>
	Line2d projectLine(Line4d<T> line) {
		return Line2d(projectPoint(line.start_), projectPoint(line.finish_));
	}
	void move_camera(Vector4d v) {
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
	void rotate_camera(double angle, int fixed_coord) {
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
  private:
  	Point4d<> camera_;
  	Point4d<> focal_point_;
  	Matrix4d transform_;
  	const Vector4d AXIS[2] = {Vector4d(1, 0, 0), Vector4d(0, 1, 0)};
};