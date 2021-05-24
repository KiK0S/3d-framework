#pragma once

#include "line.h"
#include "matrix.h"
#include "point.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace app {

/*!
    \brief Класс камеры
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Camera {
public:
    /*!
        \brief Конструктор
     */
    Camera();
    Camera(double max_x, double max_y);


    /*!
        \brief Получение видоизмененных 2д-коортинат точки
     */
    sf::Vector2f project_point(Point4d p) const;

    /*!
        \brief ОПолучаение всей точки в другом базисе.
     */
    Point4d transform_point(Point4d p) const;

    /*!
        \brief Получение третьей координаты точки
     */
    double get_z_value(Point4d p) const;

    /*!
        \brief Метод для инициализации матриц поворота
     */
    void create_transformation_matrixes();

    /*!
        \brief Метод для применения матриц поворота
     */
    void apply_transform_to_world(const Matrix4d& matrix);

    /*!
        \brief max z
     */
    double get_max_z_value() const;

    /*!
        \brief min z
     */
    double get_min_z_value() const;

    /*!
        \brief Сдвиг на вектор
     */
    void move(Point4d v);

    Point4d to_cameras_coordinates(Point4d p) const;

    double get_clipping_plane() const;

    constexpr static Point4d kLeftPoint_{-200, -200, 300};
    constexpr static Point4d kRightPoint_{200, 200, 5000};

private:
    Point4d position_{0, 0, 0};
    Matrix4d transform_space_to_screen_ = Matrix4d::identity_matrix();
    Matrix4d transform_to_camera_space_ = Matrix4d::identity_matrix();
    Matrix4d camera_rotation_ = Matrix4d::identity_matrix();
    const double kScreenHeight_;
    const double kScreenWidth_;
    const double kClipPlane_{1};
};

}
