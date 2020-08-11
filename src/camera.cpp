#include "camera.h"

namespace app {
	Camera::Camera(Screen& screen): screen_(screen),
		camera_(Point4d<double>(0, 0, 0)) {
			transform_[0][0] = 1;
			transform_[1][1] = 1;
			transform_[2][2] = 1;
			transform_[3][3] = 1;
		}

	Camera& Camera::operator = (const Camera& camera) {
		camera_ = camera.camera_;
		transform_ = camera.transform_;
		return (*this);
	}
	  	
	template <typename T>
	sf::Vector2f Camera::projectPoint(Point4d<T> p) {
		p = transform_ * p;
		if (p.z / p.w + screen_.SCREEN_SIZE / 2 > MIN_Z && p.z / p.w + screen_.SCREEN_SIZE / 2 < MAX_Z) {
			return {p.x / p.w, p.y / p.w};
		}
		return {0, 0};
	}
}