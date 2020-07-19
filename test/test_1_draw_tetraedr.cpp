#include <SFML/Graphics.hpp>
#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include "../objects/tetraedr.cpp"
#include "../drawing/animation.cpp"
#include <vector>
#include <chrono>
#include <thread>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Test 1: draw tetraedr");
    Frame frame(window);
    frame.addTetraedr(Tetraedr<>(
        Point3d<>(100, 100, 10),
        Point3d<>(200, 400, 35),
        Point3d<>(140, 900, 60),
        Point3d<>(500, 500, -10)
    ));
    frame.addTetraedr(Tetraedr<>(
        Point3d<>(900, 10, 10),
        Point3d<>(500, 890, 35),
        Point3d<>(100, 300, 60),
        Point3d<>(20, 600, -10)
    ));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        frame.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}