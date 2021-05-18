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
    void create_transform();

/*!
    \brief Метод для применения матриц поворота
 */    
    void apply_transform_to_world(const Matrix4d& matrix);

/*!
    \brief Метод для получения матриц поворота
 */
    Matrix4d get_world_transform() const;

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


private:
    static constexpr double kMinDistance_{100};
    static constexpr double kMaxDistance_{1000};

    Point4d position_{0, 0, 0};
    Matrix<3, 4> basis_screen_ = Matrix<3, 4>(std::vector<Point4d>({
        Point4d(1, 0, 0),
        Point4d(0, 1, 0),
        Point4d(0, 0, 1)
    }));
    Matrix4d transform_ = Matrix4d::identity_matrix();
    Matrix4d transform_camera_ = Matrix4d::identity_matrix();
    constexpr static Point4d kLeftPoint_{-100, -100, -100};
    constexpr static Point4d kRightPoint_{200, 200, 200};
    constexpr static double kScreenSize_{1000};
};

}
