#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Line {
  public:
    Line() = delete;
    Line(double length): length_(length) {}
    Line(double length, double angle): length_(length), angle_(angle) {}
    Line(const sf::Vector2f& start, const sf::Vector2f& finish) {
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