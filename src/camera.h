#pragma once

#include "line.h"
#include "matrix.h"
#include "point.h"
#include "screen.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace app {

class Camera {
public:
    Camera();

    sf::Vector2f project_point(Point4d p) const;
    Point4d transform_point(Point4d p) const;
    double get_z_value(Point4d p) const;

    void create_transform();
    void apply_transform_to_world(const Matrix4d& matrix);
    Matrix4d get_world_transform() const;
    double get_max_z_value() const;
    double get_min_z_value() const;
    double get_focus_distance() const;
    void move(Point4d v);

private:
    static constexpr double kMinDistance_ = 100;
    static constexpr double kFocusDistance_ = 600;
    static constexpr double kMaxDistance_ = 1100;
    const sf::Vector2f kDefaultPixel_ = sf::Vector2f(0, 0);

    Point4d position_ = Point4d(0, 0, 0);
    Point4d default_position_ = position_;
    Matrix<3, 4> basis_screen_ = Matrix<3, 4>(std::vector<Point4d>({
        Point4d(1, 0, 0),
        Point4d(0, 1, 0),
        Point4d(0, 0, 1)
    }));
    Matrix4d transform_ = Matrix4d::identity_matrix();
    Matrix4d transform_camera_ = Matrix4d::identity_matrix();
};


}
