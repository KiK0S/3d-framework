#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "line.cpp"
#include "wire_object.cpp"
#include "point.cpp"
#include "tetraedr.cpp"
#include "camera.cpp"
#include "matrix.cpp"
#include "frame.cpp"
#include "screen.cpp"
#include "cube.cpp"
#include "chair.cpp"
#include "surface_object.cpp"
#include "triangle.cpp"
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>


int main() {
    app::Screen screen;
    app::Tetraedr tetraedr(app::Point4d(100, 100, 10),
                           app::Point4d(200, 400, 35),
                           app::Point4d(140, 900, 600),
                           app::Point4d(500, 500, -10));
    app::Cube cube;
    app::Chair* chair = new app::Chair();
    // screen.add_object(tetraedr);
    // screen.add_object(cube);
    screen.add_object(chair);
    while (screen.window_.isOpen()) {
        sf::Event event;
        while (screen.window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                screen.window_.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            screen.move_camera(app::Vector4d(-1, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            screen.move_camera(app::Vector4d(1, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            screen.move_camera(app::Vector4d(0, -1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            screen.move_camera(app::Vector4d(0, 1, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            screen.move_camera(app::Vector4d(0, 0, -100));
            screen.rotate_camera(-0.01, 1);
            screen.move_camera(app::Vector4d(0, 0, 100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            screen.move_camera(app::Vector4d(0, 0, -100));
            screen.rotate_camera(0.01, 1);
            screen.move_camera(app::Vector4d(0, 0, 100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            screen.move_camera(app::Vector4d(0, 0, -100));
            screen.rotate_camera(0.01, 0);
            screen.move_camera(app::Vector4d(0, 0, 100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            screen.move_camera(app::Vector4d(0, 0, -100));
            screen.rotate_camera(-0.01, 0);
            screen.move_camera(app::Vector4d(0, 0, 100));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            screen.window_.close();
            break;
        }
        screen.update();
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
