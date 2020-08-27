#include "chair.cpp"
#include "cube.cpp"
#include "point.cpp"
#include "renderer.cpp"
#include "tetraedr.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>


void setup(app::Renderer& renderer) {
    // app::Tetraedr* tetraedr = new app::Tetraedr(app::Point4d(100, 100, 10),
    //                        app::Point4d(200, 400, 35),
    //                        app::Point4d(140, 900, 600),
    //                        app::Point4d(500, 500, -10));
    app::Cube* cube = new app::Cube();
    // app::Chair* chair = new app::Chair();
    // renderer.add_object(tetraedr);
    renderer.add_object(cube);
    // renderer.add_object(chair);
}

void handle(app::Renderer& renderer) {
    sf::Event event;
    while (renderer.window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            renderer.window_.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        renderer.move_camera(app::Vector4d(10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        renderer.move_camera(app::Vector4d(-10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        renderer.move_camera(app::Vector4d(0, 10, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        renderer.move_camera(app::Vector4d(0, -10, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        renderer.move_camera(app::Vector4d(0, 0, -100));
        renderer.rotate_camera(-0.01, 1);
        renderer.move_camera(app::Vector4d(0, 0, 100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        renderer.move_camera(app::Vector4d(0, 0, -100));
        renderer.rotate_camera(0.01, 1);
        renderer.move_camera(app::Vector4d(0, 0, 100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        renderer.move_camera(app::Vector4d(0, 0, -100));
        renderer.rotate_camera(0.01, 0);
        renderer.move_camera(app::Vector4d(0, 0, 100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        renderer.move_camera(app::Vector4d(0, 0, -100));
        renderer.rotate_camera(-0.01, 0);
        renderer.move_camera(app::Vector4d(0, 0, 100));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        renderer.window_.close();
        exit(0);
    }
    renderer.update();
}

int main() {
    app::Renderer renderer;
    setup(renderer);
    while (renderer.window_.isOpen()) {
        handle(renderer);
    }
    return 0;
}
