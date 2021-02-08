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
    void rotate_camera(const Matrix4d& matrix);
    void move_camera(const Matrix4d& matrix);
    Matrix4d get_world_transform() const;
    double get_max_z_value() const;
    double get_min_z_value() const;
    double get_focus_distance() const;
    Matrix4d get_move() const;
    Matrix4d get_rotate() const;


private:
    static constexpr double kMinDistance_ = -10000;
    static constexpr double kFocusDistance_ = 500;
    static constexpr double kMaxDistance_ = 10000;
    const sf::Vector2f kDefaultPixel_ = sf::Vector2f(0, 0);

    Renderer * const renderer_ = nullptr;

    Vector4d eye = Vector4d(0, 0, 0);
    Vector4d gaze = Vector4d(0, 0, -1);
    Vector4d up = Vector4d(0, 1, 0);
    Vector4d left = Vector4d(1, 0, 0);

    // Point4d position_ = Point4d(0, 0, -kFocusDistance_);
    Matrix<4, 2> basis_screen_ = Matrix<4, 2>::identity_matrix();
    Matrix4d basis_world_ = Matrix4d::identity_matrix();
    Matrix4d transform_ = Matrix4d::identity_matrix();
};


}
