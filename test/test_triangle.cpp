#include "triangle.cpp"
#include "point.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    app::Triangle2d t(sf::Vector2f(1, 3), sf::Vector2f(5, -2), sf::Vector2f(-3, 1));
    for (double x = -5; x <= 5; x += 0.2) {
        for (double y = -5; y <= 5; y += 0.2) {
            std::cout << t.inner_point(sf::Vector2f(x, y)) << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
