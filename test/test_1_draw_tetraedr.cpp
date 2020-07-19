#include <SFML/Graphics.hpp>
#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include "../objects/tetraedr.cpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Test 1: draw tetraedr");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        std::vector<Line> to_draw = Tetraedr<>(
            Point3d<>(100, 100, 10),
            Point3d<>(200, 400, 35),
            Point3d<>(140, 900, 60),
            Point3d<>(500, 500, -10)
        ).lines();
        for (auto& line : to_draw) {
            line.draw(window);
        }
        window.display();
    }

    return 0;
}