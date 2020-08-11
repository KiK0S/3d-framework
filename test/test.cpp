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
#include "cube.h"
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>


int main() {
    app::Screen screen;
    app::Tetraedr<double> tetraedr(app::Point3d<double>(100, 100, 10),
                                   app::Point3d<double>(200, 400, 35),
                                   app::Point3d<double>(140, 900, 600),
                                   app::Point3d<double>(500, 500, -10));
    app::Cube<double> cube;
    // screen.frame_->add_object(tetraedr);
    screen.frame_->add_object(cube);
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
            screen.rotate_camera(-0.01, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            screen.rotate_camera(0.01, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            screen.rotate_camera(0.01, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            screen.rotate_camera(-0.01, 0);
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