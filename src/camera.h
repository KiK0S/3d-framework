#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "classes.h"
#include "line.h"
#include "point.h"
#include "matrix.h"
#include "screen.h"

namespace app {

class Camera {
public:
    Camera() = delete;
    Camera(Screen& screen);
    Camera& operator = (const Camera& camera);

    template <typename T>
    sf::Vector2f project_point(Point4d<T> p) const;

    void apply_matrix(Matrix4d matrix);
    Matrix4d inverse() const;

private:
    Screen& screen_;
    Point4d<> camera_;
    Matrix4d transform_;
    double MAX_Z = 100000;
    double MIN_Z = -100000;
};

}
