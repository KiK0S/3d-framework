#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../objects/point.cpp"

class Line2d {
  public:
    Line2d() = delete;
    Line2d(double length): length_(length) {}
    Line2d(double length, double angle): length_(length), angle_(angle) {}
    Line2d(const sf::Vector2f& start, const sf::Vector2f& finish) {
        offset_ = start;
        sf::Vector2f vector = finish - start;
        sf::Vector2f norm(-vector.y, vector.x);
        length_ = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        angle_ = std::atan2(vector.y, vector.x) * 180 / atan2(0, -1);
        if (angle_ < 0) {
            angle_ += 360;
        }
    }
    void draw(sf::RenderWindow & window) {
        sf::RectangleShape shape(sf::Vector2f(length_, WIDTH));
        shape.setFillColor(sf::Color::Black);
        shape.setRotation(angle_);
        shape.setPosition(offset_);
        window.draw(shape);
    }
  private:
    double length_;
    double angle_;
    sf::Vector2f offset_;
    const float WIDTH = 1.5f;
};

template <typename T = double>
class Line3d {
  public:
    Line3d() = delete;
    Line3d(const Point3d<T>& start, const Point3d<T>& finish): start_(start), finish_(finish) {}
    Point3d<T> start_, finish_;
};

template <typename T = double>
class Line4d {
  public:
    Line4d() = delete;
    Line4d(const Point4d<T>& start, const Point4d<T>& finish): start_(start), finish_(finish) {}
    Point4d<T> start_, finish_;
};