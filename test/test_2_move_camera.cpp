#include <SFML/Graphics.hpp>
#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include "../objects/tetraedr.cpp"
#include "../drawing/animation.cpp"
#include "../camera/camera.cpp"
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
    frame.addCamera(Camera());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        frame.update();
        frame.camera_.move_camera();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}