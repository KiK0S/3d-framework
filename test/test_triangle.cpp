#include "triangle.cpp"
#include "point.cpp"
#include "renderer.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	app::Renderer renderer;
    app::Triangle2d t(sf::Vector2f(1, 3), sf::Vector2f(5, -2), sf::Vector2f(-3, 1));
    for (double x = -5; x <= 5.1; x += 0.2) {
        for (double y = -5; y <= 5.1; y += 0.2) {
            std::cout << t.inner_point(sf::Vector2f(x, y)) << ' ';
        }
        std::cout << renderer.find_min_y(t, x) << " ";
        std::cout << renderer.find_max_y(t, x);
        std::cout << std::endl;
    }
    return 0;
}
