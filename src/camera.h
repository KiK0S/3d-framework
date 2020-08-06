#pragma once

#include "line.h"
#include "point.h"
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include <cmath>

class Camera {
  public:
  	Camera();
  	Camera& operator = (const Camera& camera);

  	template <typename T>
  	sf::Vector2f projectPoint(Point4d<T> p);

	template <typename T>
	Line2d projectLine(Line4d<T> line);

	void move_camera(Vector4d v);

	void rotate_camera(double angle, int fixed_coord);

	void draw_axis(sf::RenderWindow& window);
  private:
  	Point4d<> camera_;
  	Point4d<> focal_point_;
  	Matrix4d transform_;
  	const Vector4d AXIS[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
  	const sf::Color COLORS[3] = {sf::Color::Green, sf::Color::Red, sf::Color::Blue};
};