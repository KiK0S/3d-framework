#include "camera.cpp"
#include "chair.cpp"
#include "cube.cpp"
#include "frame.cpp"
#include "line.cpp"
#include "matrix.cpp"
#include "point.cpp"
#include "screen.cpp"
#include "surface_object.cpp"
#include "tetraedr.cpp"
#include "triangle.cpp"
#include "wire_object.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>


void setup(app::Screen& screen) {
    app::Tetraedr* tetraedr = new app::Tetraedr(app::Point4d(100, 100, 10),
                           app::Point4d(200, 400, 35),
                           app::Point4d(140, 900, 600),
                           app::Point4d(500, 500, -10));
    app::Cube* cube = new app::Cube();
    app::Chair* chair = new app::Chair();
    screen.add_object(tetraedr);
    screen.add_object(cube);
    screen.add_object(chair);
}

void handle(app::Screen& screen) {
    sf::Event event;
    while (screen.window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            screen.window_.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        screen.move_camera(app::Vector4d(10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        screen.move_camera(app::Vector4d(-10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        screen.move_camera(app::Vector4d(0, 10, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        screen.move_camera(app::Vector4d(0, -10, 0));
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
        exit(0);
    }
    screen.update();
}

int main() {
    app::Screen screen;
    setup(screen);
    while (screen.window_.isOpen()) {
        handle(screen);
    }
    return 0;
}
