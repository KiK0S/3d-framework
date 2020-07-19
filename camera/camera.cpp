#pragma once


#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include <SFML/Graphics.hpp>

namespace Camera {
	template <typename T>
	Line projectLine(Point3d<T> a, Point3d<T> b) {
		return Line(sf::Vector2f(a.x, a.y), sf::Vector2f(b.x, b.y));
	}
};