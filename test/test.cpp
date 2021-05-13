#include "application.h"
#include "chair.h"
#include "cube.h"
#include "point.h"
#include "tetraedr.h"
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


void setup(app::Application& application) {
    app::Cube* cube = new app::Cube();
    application.add_object(cube);
}

void handle(app::Application& application) {
    sf::Event event;
    while (application.poll_event(event)) {
        if (event.type == sf::Event::Closed) {
            application.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        application.move_camera(app::Vector4d(10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        application.move_camera(app::Vector4d(-10, 0, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        application.move_camera(app::Vector4d(0, 10, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        application.move_camera(app::Vector4d(0, -10, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        application.move_camera(app::Vector4d(0, 0, 10));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        application.move_camera(app::Vector4d(0, 0, -10));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        application.yaw(0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        application.yaw(-0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        application.pitch(0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        application.pitch(-0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        application.roll(0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        application.roll(-0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        application.azimuth(0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        application.azimuth(-0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        application.elevation(0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        application.elevation(-0.01);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        application.close();
        exit(0);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    application.update();
}

int main() {
    app::Application application;
    setup(application);
    while (application.is_open()) {
        handle(application);
    }
    return 0;
}
