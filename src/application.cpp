#include "application.h"
#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application(): world_(), renderer_(),
                            window_(sf::VideoMode(kScreenSize_, kScreenSize_),
                                    "Test: interacrtive camera") {}

void Application::update() {
    debug("new frame");
    window_.clear(sf::Color::White);
    renderer_.prepare();
    int lines = 0;
    int triangles = 0;
    for (auto& object : world_) {
        for (auto& triangle : object->triangles()) {
            renderer_.draw(triangle);
            triangles++;
        }
        for (auto& line3d : object->lines()) {
            renderer_.draw(line3d, window_);
            lines++;
        }
    }
    renderer_.update(window_);
    window_.display();
    debug("/////////////");
}

void Application::move_camera(Vector4d v) {
    renderer_.move_camera(v);
}

void Application::move_world(Vector4d v) {
    // v = v;
    Matrix4d moving = Matrix4d::identity_matrix();
    moving(0, 3) = v.x;
    moving(1, 3) = v.y;
    moving(2, 3) = v.z;
    for (std::unique_ptr<SurfaceObject>& object : world_) {
        for (Point4d& p : (*object)) {
            p = moving * p;
        }
    }
}

void Application::add_object(std::unique_ptr<SurfaceObject>&& w) {
    world_.add_object(std::move(w));
}

bool Application::poll_event(sf::Event& event) {
    return window_.pollEvent(event);
}

bool Application::is_open() const {
    return window_.isOpen();
}

void Application::close() {
    window_.close();
}

void Application::roll(double angle) {
    renderer_.rotate_world(angle, 2);
}

void Application::pitch(double angle) {
    renderer_.rotate_camera(angle, 1);
}
 
void Application::yaw(double angle) {
    renderer_.rotate_camera(angle, 0);
}

void Application::elevation(double angle) {
    renderer_.rotate_world(angle, 0);
}

void Application::azimuth(double angle) {
    renderer_.rotate_world(angle, 1);
}


void Application::run() {
    while (is_open()) {
        sf::Event event;
        while (poll_event(event)) {
            if (event.type == sf::Event::Closed) {
                close();
                return;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            move_camera(app::Vector4d(10, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            move_camera(app::Vector4d(-10, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            move_camera(app::Vector4d(0, 10, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            move_camera(app::Vector4d(0, -10, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            move_camera(app::Vector4d(0, 0, 10));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            move_camera(app::Vector4d(0, 0, -10));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            yaw(0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            yaw(-0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pitch(0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pitch(-0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            roll(0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            roll(-0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            azimuth(0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            azimuth(-0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            elevation(0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            elevation(-0.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            close();
            return;
        }
        update();
    }
}

}
