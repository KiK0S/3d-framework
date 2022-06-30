#include "application.h"
#include "cube.h"
#include "point.h"
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void rotate(float angle, app::Application& app) {
    auto current_rotation = app.get_camera().get_rotation();
    app.get_camera().rotate(current_rotation.transpose() * app::Matrix4d::construct_rotation_matrix(1, angle) * current_rotation);
}

int main() {
    app::Application application(false);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int rA = rand() % 100;
            int rB = rand() % 100;
            int rC = rand() % 100;
            application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{20.0 + 50 * i, 20.0, -20.0 + 50 * j}, sf::Color(rA, rB, rC)));
        }
    }
    double velocityZ = 0;
    double last_pitch = 0;
    double last_yaw = 0;
    application.get_camera().move({0, -50, 0});
    while (application.is_open()) {
        sf::Event event;
        while (application.poll_event(&event)) {
            if (event.type == sf::Event::Closed) {
                application.close();
                return 0;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            application.move_camera(app::Vector4d(0, 0, 10));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            application.move_camera(app::Vector4d(0, 0, -10));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rotate(-0.1, application);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rotate(0.1, application);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            application.move_camera(app::Vector4d(0, -10, 0));
            velocityZ += 10;
        }
        if (velocityZ > 0) {
            velocityZ -= 1;
            application.move_camera(app::Vector4d(0, 1, 0));
        }

        auto mouse = sf::Mouse::getPosition(application.get_window());
        auto pitch = 6.28 * (int(mouse.x) - int(application.kScreenWidth) / 2) * 1.0 / application.kScreenWidth;
        auto yaw = -6.28 * (int(mouse.y) - int(application.kScreenHeight) / 2) * 1.0 / application.kScreenHeight;
        application.yaw(-last_yaw);
        application.pitch(-last_pitch);
        application.pitch(pitch);
        application.yaw(yaw);
        last_pitch = pitch;
        last_yaw = yaw;
        application.update_and_draw_frame();
    }
    return 0;
}