#include <SFML/Graphics.hpp>

class Line {
  public:
    Line() = delete;
    Line(double length): length_(length) {}
    Line(double length, double angle): length_(length), angle_(angle) {}
    void draw(sf::RenderWindow & window) {
        sf::RectangleShape shape(sf::Vector2f(length_, WIDTH));
        shape.setFillColor(sf::Color::Black);
        shape.setRotation(angle_);
        window.draw(shape);
    }
  private:
    double length_;
    double angle_;
    const double WIDTH = 5.0f;
};