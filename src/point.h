#pragma once

#include <SFML/Graphics.hpp>

namespace app {

/*!
    \brief Класс четырехмерной точки.

    Есть явное соответствие между 3d-точкой и 4d-точкой. (x, y, z) -> (x, y, z, 1); (x, y, z, w) -> (x / w, y / w, z / w)
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Point4d {
public:
    double x, y, z, w;

    /*!
        \brief Создает нулевую точку
     */
    Point4d();

    /*!
        \brief Создает точку по трехмерной точке
     */
    constexpr Point4d(const std::initializer_list<double>& args): x(*args.begin()), y(*(args.begin() + 1)), z(*(args.begin() + 2)), w(1) {}

    /*!
        \brief Создает точку по трехмерной точке
     */
    constexpr Point4d(double x, double y, double z): x(x), y(y), z(z), w(1) {}

    /*!
        \brief Прибавляет другую точку по правилу сложения трехмерных точек
     */
    Point4d& operator += (const Point4d& p);

    /*!
        \brief Вычитает другую точку по правилу сложения трехмерных точек
     */
    Point4d& operator -= (const Point4d& p);

    /*!
        \brief Увеличивает координаты в f раз
     */
    Point4d& operator *= (double f);

    /*!
        \brief Уменьшает координаты в f раз
     */
    Point4d& operator /= (double f);

    /*!
        \brief Складывает точки по правилу сложения трехмерных точек
     */
    friend Point4d operator + (const Point4d& a, const Point4d& b);

    /*!
        \brief Вычитает точки по правилу сложения трехмерных точек
     */
    friend Point4d operator - (const Point4d& a, const Point4d& b);

    /*!
        \brief Увеличивает координаты точки в d раз
     */
    friend Point4d operator * (const Point4d& a, double d);

    /*!
        \brief Уменьшает координаты точки в d раз
     */
    friend Point4d operator / (const Point4d& a, double d);

    /*!
        \brief Увеличивает координаты точки в d раз
     */
    friend Point4d operator * (double d, const Point4d& p);

    /*!
        \brief Проверяет точки на равенство
     */
    friend bool operator == (const Point4d& a, const Point4d& b);

    /*!
        \brief Возвращает i-ю координату точки
     */
    double operator() (size_t i) const ;

    /*!
        \brief Возвращает i-ю координату точки
     */
    double& operator() (size_t i) ;

    /*!
        \brief Возвращает расстояние от точки (0, 0) до x
     */
    double length() const ;

    /*!
        \brief Нормализует координаты точки - получает соответствующую трехмерную с w = 1
     */
    void normalize() ;

    /*!
        \brief Меняет длину вектора на d
     */
    void resize(double d) ;

    /*!
        \brief проверяет вектора на сонаправленность
        \param p Вектор, который проверяется на сонаправленность данному
     */
    bool is_collinear(const Point4d& b) const ;
};

using Vector4d = Point4d;

double cross(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const Vector4d& a, const Vector4d& b);
sf::Vector2f& operator *= (sf::Vector2f& v, double d);
sf::Vector2f& operator /= (sf::Vector2f& v, double d);

Point4d operator + (const Point4d& a, const Point4d& b) ;
Point4d operator - (const Point4d& a, const Point4d& b) ;
Point4d operator * (const Point4d& a, double d) ;
Point4d operator * (double d, const Point4d& a) ;
Point4d operator / (const Point4d& a, double d) ;
bool operator == (const Point4d& a, const Point4d& b) ;


double length(const sf::Vector2f& v);

}
