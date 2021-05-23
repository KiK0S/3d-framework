#include "application.h"
#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application(): world_(), camera_(), renderer_(camera_.kRightPoint_.z), 
                            window_(sf::VideoMode(kScreenWidth_, kScreenHeight_),
                                    "Test: interacrtive camera") {}

void Application::update() {
    debug("new frame");
    window_.clear(sf::Color::White);
    camera_.create_transform();
    int lines = 0;
    int triangles = 0;
    for (auto& object : world_) {
        for (auto& triangle4d : object->triangles()) {
            for (auto& triangle : renderer_.clip(camera_, triangle4d)) {
                renderer_.draw(camera_, triangle);
                triangles++;
            }
        }
        for (auto& line3d : object->lines()) {
            renderer_.draw(line3d, window_, camera_);
            lines++;
        }
    }
    renderer_.update(window_);
    for (auto& object : world_) {
        for (auto& line3d : object->lines()) {
            renderer_.draw(line3d, window_, camera_);
            lines++;
        }
    }
    window_.display();
    debug("/////////////");
}

void Application::move_camera(Vector4d v) {
    // move_world(v);
    camera_.move(v);
}

void Application::move_world(Vector4d v) {
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

void Application::rotate_world(double angle, Application::EAxes axe) {
    int fixed_coord = 0;
    switch (axe) {
    case EAxes::AXE_X:
        fixed_coord = 0;
        break;
    case EAxes::AXE_Y:
        fixed_coord = 1;
        break;
    case EAxes::AXE_Z:
        fixed_coord = 2;
        break;
    }
    Matrix4d moving = Matrix4d::identity_matrix();
    moving((fixed_coord + 1) % 3, (fixed_coord + 1) % 3) = std::cos(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 2) % 3) = std::cos(angle);
    moving((fixed_coord + 1) % 3, (fixed_coord + 2) % 3) = std::sin(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 1) % 3) = -std::sin(angle);
    camera_.apply_transform_to_world(moving);
}


void Application::roll(double angle) {
    rotate_world(angle, EAxes::AXE_Z);
}

void Application::pitch(double angle) {
    rotate_world(angle, EAxes::AXE_Y);
}
 
void Application::yaw(double angle) {
    rotate_world(angle, EAxes::AXE_X);
}

void Application::elevation(double angle) {
    rotate_world(angle, EAxes::AXE_X);
}

void Application::azimuth(double angle) {
    rotate_world(angle, EAxes::AXE_Y);
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
