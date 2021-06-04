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

    Класс Camera отвечает за то, чтобы переводить объекты из системы координат мира
    в систему координат экрана. Для этого этот объект генерирует матрицу преобразования
    ии применяет ее к точкам, которые надо отобразить.
    Камеру можно поворачивать и двигать, что отражается на матрице преобразования.
*/
class Camera {
public:
    /*!
        \brief Конструктор
        \param screen_width ширина экрана, на кеторый будет проецироваться изображение
        \param screen_height высота экрана, на кеторый будет проецироваться изображение
     */
    Camera(double screen_width, double screen_height);

    /*!
        \brief Перевод точки в координатную систему камеры
        \param p Точка, которая переводится в координатную систему камеры
        \returns Точка после поворота и сдвига, в координатной системе камеры
     */
    Point4d transform_to_cameras_coordinates(const Point4d& p) const;

    /*!
        \brief Получение координат на в пространстве (экран, z-value)
        \param p Точка, которая переводится в пространство (экран, z-value)
        \returns Точка после преобразваний, в координатной системе (экран, z-value)
     */
    Point4d transform_to_screen(const Point4d& p) const;

    /*!
        \brief Получение видоизмененных 2д-коортинат точки
        \param p Точка, которая переносится на экран
        \returns Проекция точки на экран
     */
    sf::Vector2f project_on_screen(const Point4d& p) const;

    /*!
        \brief Получение z-value точки
        \param p Точка, у которой ищется z-value
        \returns z-value точки
     */
    double get_z_value(const Point4d& p) const;

    /*!
        \brief Метод для применения матриц поворота
        \param matrix. Матрица поворотп
    */
    void rotate(const Matrix4d& matrix);

    /*!
        \brief min z
        \returns Минимальная z-value, которая перенесется на экран
     */
    double get_min_z_value() const;

    /*!
        \brief Сдвиг на вектор
        \param v вектор сдвига
     */
    void move(const Point4d& v);

    /*!
        \brief Расстояние до ближайшей плоскости обзора
        \returns Расстояние до плоскости, ближе которой камера не видит
     */
    double get_clipping_plane_distance() const;

    /*!
        \brief Вернуть матрицу поворота камеры
     */
    Matrix4d get_rotation() const;

private:
    /*!
        \brief Метод для инициализации матриц поворота
     */
    void create_transformation_matrixes();


    Point4d focus_point_{0, 0, 0};
    Matrix4d transform_space_to_screen_ = Matrix4d::identity_matrix();
    Matrix4d transform_to_camera_space_ = Matrix4d::identity_matrix();
    Matrix4d camera_rotation_ = Matrix4d::identity_matrix();
    constexpr static Point4d kLeftPoint_{-200, -200, 400};
    constexpr static Point4d kRightPoint_{200, 200, 5000};
    constexpr static double kClippingPlaneDistance_{1};
    double kScreenHeight_;
    double kScreenWidth_;
};

}
