#include "application.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application():
    world_(), camera_(kScreenWidth_, kScreenHeight_),
    renderer_(kScreenWidth_, kScreenHeight_, 50000),
    window_(sf::VideoMode(kScreenWidth_, kScreenHeight_),
            "Test: interacrtive camera") {}

void Application::update_and_draw_frame() {
    window_.clear(sf::Color::White);
    camera_.create_transformation_matrixes();
    for (auto& object_ptr : world_) {
        draw_object(object_ptr);
    }
    renderer_.draw_frame(window_);
    window_.display();
}

void Application::add_object(std::unique_ptr<SurfaceObject>&& w) {
    world_.add_object(std::move(w));
}

void Application::move_camera(const Vector4d& v) {
    camera_.move(v);
}

void Application::move_world(const Vector4d& v) {
    Matrix4d transform = construct_moving_matrix(v);
    for (auto& object_ptr : world_) {
        object_ptr->apply_transform(transform);
    }
}

void Application::roll(double angle) {
    rotate_world(angle, EAxes::AXE_Z);
}

void Application::pitch(double angle) {
    rotate_world(angle, EAxes::AXE_Y);
}

void Application::elevation(double angle) {
    rotate_world(angle, EAxes::AXE_X);
}

void Application::azimuth(double angle) {
    rotate_world(angle, EAxes::AXE_Y);
}

void Application::yaw(double angle) {
    rotate_world(angle, EAxes::AXE_X);
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
        update_and_draw_frame();
    }
}

void Application::rotate_world(double angle, Application::EAxes axe) {
    int fixed_coord = convert_axis_to_int(axe);
    Matrix4d transform = construct_rotation_matrix(fixed_coord, angle);
    camera_.apply_transform_to_world(transform);
}

int Application::convert_axis_to_int(const Application::EAxes& axe) {
    switch (axe) {
    case EAxes::AXE_X:
        return 0;
    case EAxes::AXE_Y:
        return 1;
    case EAxes::AXE_Z:
        return 2;
    }
    assert(false);
    return -1;
}

Matrix4d Application::construct_moving_matrix(const Vector4d& moving_vector) {
    Matrix4d move = Matrix4d::identity_matrix();
    assert(moving_vector.w != 0);
    move(0, 3) = moving_vector.x / moving_vector.w;
    move(1, 3) = moving_vector.y / moving_vector.w;
    move(2, 3) = moving_vector.z / moving_vector.w;
    return move;
}

Matrix4d Application::construct_rotation_matrix(int fixed_coordinate, double angle) {
    // oX, oY, oZ <-> 0, 1, 2
    assert(fixed_coordinate >= 0 && fixed_coordinate <= 2);
    Matrix4d rotation = Matrix4d::identity_matrix();
    rotation((fixed_coordinate + 1) % 3, (fixed_coordinate + 1) % 3) = std::cos(angle);
    rotation((fixed_coordinate + 2) % 3, (fixed_coordinate + 2) % 3) = std::cos(angle);
    rotation((fixed_coordinate + 1) % 3, (fixed_coordinate + 2) % 3) = std::sin(angle);
    rotation((fixed_coordinate + 2) % 3, (fixed_coordinate + 1) % 3) = -std::sin(angle);
    return rotation;
}

void Application::draw_object(const std::unique_ptr<SurfaceObject>& object_ptr) {
    for (auto& triangle4d : object_ptr->triangles()) {
        draw_triangle(triangle4d);
    }
}

void Application::draw_triangle(const Triangle4d& triangle4d) {
    for (auto& triangle2d : renderer_.clip_triangle(camera_, triangle4d)) {
        renderer_.draw_triangle(camera_, triangle2d);
    }
}

}
