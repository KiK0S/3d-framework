#pragma once

#include "matrix.h"
#include "point.h"
#include <SFML/Graphics.hpp>
#include <array>

namespace app {
/*!
    \brief Класс треугольника в 4д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class Triangle4d {
public:
    /*!
        \brief Конструктор треугольника
     */
    Triangle4d(Point4d a, Point4d b, Point4d c, sf::Color color = sf::Color::Black);

    /*!
        \brief Выдает вершины треугольника в нужном порядке
     */
    void get_points(std::array<int, 3> order, Point4d* a, Point4d* b, Point4d* c) const ;

    /*!
        \brief Возвращает цвет треугольника
     */
    sf::Color get_color() const ;

    /*!
        \brief Возвращает цвет треугольника с учетом тени
     */
    sf::Color get_shadowed_color() const ;

    /*!
        \brief Возвращает вектор нормали к плоскости треугольника длины 1
     */
    Vector4d get_normal_vector() const ;

    Point4d a, b, c;
private:
    sf::Color color_;
};
/*!
    \brief Класс треугольника в 2д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class Triangle2d {
public:
    /*!
        \brief Конструктор треугольника
     */
    Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);

    /*!
        \brief Проверяет, что точка внутри треугольника
     */
    bool inner_point(const sf::Vector2f& o) const ;

    /*!
        \brief Возвращает самую левую точку треугольника
     */
    sf::Vector2f get_left_point() const ;

    /*!
        \brief Возвращает самую правую точку треугольника
     */
    sf::Vector2f get_right_point() const ;

    /*!
        \brief Возвращает минимальную y-координату точки треугольника с заданной x-координатой
     */
    double min_y_in_line(double x) const ;

    /*!
        \brief Возвращает максимальную y-координату точки треугольника с заданной x-координатой
     */
    double max_y_in_line(double x) const ;

    /*!
        \brief Создает два базисных вектора треугольника

        Вектора сделаны так, что в паре с точкой A образуют векторное пространство, а треугольник натянут на точку A
     */
    Matrix<2, 2> create_basis() const ;

    /*!
        \brief Возвращает порядок, в котором точки a, b, c отсортированы относительно того порядка, который был передан в конструктор
     */
    std::array<int, 3> get_order() const ;

    /*!
        \brief Вычисляет площадь треугольника
     */
    double square() const ;

    /*!
        \brief Проверка треугольника на вырожденность
     */
    bool is_degenerate() const ;

    sf::Vector2f a, b, c;
private:
    std::array<int, 3> order_;
};

}
