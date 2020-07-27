#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../drawing/line.cpp"
#include "../objects/point.cpp"
#include "../objects/tetraedr.cpp"
#include "../drawing/animation.cpp"
#include "../camera/camera.cpp"
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>


const int WINDOW_SIZE = 1000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Test 3: interacrtive camera");
    Frame frame(window);
    frame.addObject(Tetraedr<>(
        Point3d<>(100, 100, 10),
        Point3d<>(200, 400, 35),
        Point3d<>(140, 900, 600),
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            frame.camera_.move_camera(Vector4d(-1, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            frame.camera_.move_camera(Vector4d(1, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            frame.camera_.move_camera(Vector4d(0, -1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            frame.camera_.move_camera(Vector4d(0, 1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            frame.camera_.rotate_camera(-0.01, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            frame.camera_.rotate_camera(0.01, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            frame.camera_.rotate_camera(0.01, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            frame.camera_.rotate_camera(-0.01, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            break;
        }
        frame.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}