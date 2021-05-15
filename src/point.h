#pragma once

#include <SFML/Graphics.hpp>

namespace app {

/*!
    \brief Класс четырехмерной точки.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Point4d {
public:
    double x, y, z, w;
    Point4d() = delete;
    Point4d(const std::initializer_list<double>& args): x(*args.begin()), y(*(args.begin() + 1)), z(*(args.begin() + 2)), w(*(args.begin() + 3)) {}
    constexpr Point4d(double x, double y, double z): x(x), y(y), z(z), w(1) {}
    Point4d(sf::Vector3f v);


    Point4d operator + (const Point4d& p) const ;
    Point4d operator - (const Point4d& p) const ;
    Point4d operator * (double f) const ;
    Point4d operator / (double f) const ;
    Point4d& operator += (const Point4d& p);
    Point4d& operator -= (const Point4d& p);
    Point4d& operator *= (double f);
    Point4d& operator /= (double f);
    double operator[] (size_t i) const ;
    double& operator[] (size_t i) ;
    double length() const ;
};

using Vector4d = Point4d;

Point4d operator * (double f, const Point4d& p);

double cross(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const Vector4d& a, const Vector4d& b);

sf::Vector2f& operator*= (sf::Vector2f& v, double d);
sf::Vector2f& operator/= (sf::Vector2f& v, double d);

double length(const sf::Vector2f& v);

}
