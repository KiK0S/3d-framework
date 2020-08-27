#pragma once

#include "line.h"
#include "matrix.h"
#include "point.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace app {

class Renderer;
class Camera {
public:
    Camera(Renderer* renderer);

    sf::Vector2f project_point(Point4d p) const;
    Point4d transform_point(Point4d p) const;
    double get_z_value(Point4d p) const;

    void create_transform();
    void apply_transform_to_camera(const Matrix4d& matrix);
    void apply_transform_to_world(const Matrix4d& matrix);
    Matrix4d get_world_transform() const;
    double get_max_z_value() const;

private:
    static constexpr double kMinDistance = 100;
    static constexpr double kFocusDistance = 500;
    static constexpr double kMaxDistance = 1000;
    const sf::Vector2f kDefaultPixel = sf::Vector2f(0, 0);

    Renderer* renderer_ = nullptr;

    Point4d position_ = Point4d(0, 0, -kFocusDistance);
    Matrix<4, 2> basis_screen_ = Matrix<4, 2>::identity_matrix();
    Matrix4d basis_world_ = Matrix4d::identity_matrix();
    Matrix4d transform_ = Matrix4d::identity_matrix();
};


}
