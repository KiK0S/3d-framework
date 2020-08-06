#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../src/line.cpp"
#include "../src/point.cpp"
#include "../src/tetraedr.cpp"
#include "../src/animation.cpp"
#include "../src/camera.cpp"
#include "../src/matrix.cpp"
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>


const int WINDOW_SIZE = 1000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Test 3: interacrtive camera");
    Frame frame(window);
    Tetraedr<double> tetraedr(Point3d<double>(100, 100, 10),
        Point3d<double>(200, 400, 35),
        Point3d<double>(140, 900, 600),
        Point3d<double>(500, 500, -10));
    frame.addObject(tetraedr);
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