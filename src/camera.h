#pragma once

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
    Camera(double screen_width, double screen_height);

    /*!
        \brief Перевод точки в координатную систему камеры
     */

    Point4d transform_to_cameras_coordinates(const Point4d& p) const;

    /*!
        \brief Получение координат на в пространстве (экран, z-value)
     */
    Point4d transform_to_screen(const Point4d& p) const;

    /*!
        \brief Получение видоизмененных 2д-коортинат точки
     */
    sf::Vector2f project_on_screen(const Point4d& p) const;

    /*!
        \brief Получение z-value точки
     */
    double get_z_value(const Point4d& p) const;

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
    void move(const Point4d& v);

    /*!
        \brief Расстояние до ближайшей плоскости обзора
     */
    double get_clipping_plane_distance() const;

private:
    Point4d focus_point_{0, 0, 0};
    Matrix4d transform_space_to_screen_ = Matrix4d::identity_matrix();
    Matrix4d transform_to_camera_space_ = Matrix4d::identity_matrix();
    Matrix4d camera_rotation_ = Matrix4d::identity_matrix();
    constexpr static Point4d kLeftPoint_{-200, -200, 300};
    constexpr static Point4d kRightPoint_{200, 200, 5000};
    constexpr static double kClippingPlaneDistance_{1};
    double kScreenHeight_;
    double kScreenWidth_;
};

}
