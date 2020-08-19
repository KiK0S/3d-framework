#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "line.h"
#include "point.h"
#include "matrix.h"
#include "screen.h"

namespace app {
class Screen;
class Camera {
public:
    Camera(Screen* screen);

    sf::Vector2f project_point(Point4d p) const;
    double get_z_value(Point4d p) const;

    void apply_matrix(Matrix4d matrix);
    Matrix4d find_inverse_transform() const;

private:
    Screen* screen_ = nullptr;
    Point4d camera_;
    Matrix4d transform_;
    double MAX_Z = 100000;
    double MIN_Z = -100000;
};

}
