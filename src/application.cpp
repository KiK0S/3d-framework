#include "application.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application(bool def = true):
    world_(), camera_(kScreenWidth, kScreenHeight),
    renderer_(kScreenWidth, kScreenHeight),
    window_(sf::VideoMode(kScreenWidth, kScreenHeight),
            "My3dFramework Application") {
    if (def) {
        create_keyboard_handlers();
    }
}

void Application::update_and_draw_frame() {
    window_.clear(sf::Color::White);
    for (auto& object_ptr : world_) {
        draw_object(object_ptr);
    }
    renderer_.draw_frame(window_);
    window_.display();
}

void Application::move_camera(const Vector4d& v) {
    camera_.move(v);
}

void Application::move_world(const Vector4d& v) {
    Matrix4d transform = Matrix4d::construct_moving_matrix(camera_.get_rotation().transpose() * v);
    for (auto& object_ptr : world_) {
        object_ptr->apply_transform(transform);
    }
}

void Application::roll(double angle) {
    rotate_camera(angle, EAxes::AXE_Z);
}

void Application::pitch(double angle) {
    rotate_camera(angle, EAxes::AXE_Y);
}

void Application::yaw(double angle) {
    rotate_camera(angle, EAxes::AXE_X);
}

bool Application::poll_event(sf::Event* event) {
    return window_.pollEvent(*event);
}

bool Application::is_open() const {
    return window_.isOpen();
}

const World& Application::get_world() const {
    return world_;
}

World& Application::get_world() {
    return world_;
}

Camera& Application::get_camera() {
    return camera_;
}

const sf::RenderWindow& Application::get_window() const {
    return window_;
}

void Application::close() {
    window_.close();
}

void Application::run() {
    while (is_open()) {
        sf::Event event;
        while (poll_event(&event)) {
            if (event.type == sf::Event::Closed) {
                close();
                return;
            }
        }
        for (const auto& [key, handler] : keyboard_handlers_) {
            if (sf::Keyboard::isKeyPressed(key)) {
                handler();
            }
        }
        update_and_draw_frame();
    }
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

void Application::rotate_camera(double angle, Application::EAxes axe) {
    int fixed_coord = convert_axis_to_int(axe);
    Matrix4d transform = Matrix4d::construct_rotation_matrix(fixed_coord, angle);
    camera_.rotate(transform);
}

void Application::draw_object(const std::unique_ptr<SurfaceObject>& object_ptr) {
    for (auto& triangle4d : object_ptr->get_triangles()) {
        renderer_.draw_triangle(camera_, triangle4d);
    }
}

void Application::create_keyboard_handlers() {
    keyboard_handlers_ = {
        {   sf::Keyboard::Left, [this]() {
                move_camera(app::Vector4d(10, 0, 0));
            }
        },
        {   sf::Keyboard::Right, [this]() {
                move_camera(app::Vector4d(-10, 0, 0));
            }
        },
        {   sf::Keyboard::Down, [this]() {
                move_camera(app::Vector4d(0, -10, 0));
            }
        },
        {   sf::Keyboard::Up, [this]() {
                move_camera(app::Vector4d(0, 10, 0));
            }
        },
        {   sf::Keyboard::Z, [this]() {
                move_camera(app::Vector4d(0, 0, 10));
            }
        },
        {   sf::Keyboard::X, [this]() {
                move_camera(app::Vector4d(0, 0, -10));
            }
        },
        {   sf::Keyboard::J, [this]() {
                move_world(app::Vector4d(10, 0, 0));
            }
        },
        {   sf::Keyboard::L, [this]() {
                move_world(app::Vector4d(-10, 0, 0));
            }
        },
        {   sf::Keyboard::K, [this]() {
                move_world(app::Vector4d(0, -10, 0));
            }
        },
        {   sf::Keyboard::I, [this]() {
                move_world(app::Vector4d(0, 10, 0));
            }
        },
        {   sf::Keyboard::U, [this]() {
                move_world(app::Vector4d(0, 0, 10));
            }
        },
        {   sf::Keyboard::O, [this]() {
                move_world(app::Vector4d(0, 0, -10));
            }
        },
        {   sf::Keyboard::A, [this]() {
                yaw(0.01);
            }
        },
        {   sf::Keyboard::D, [this]() {
                yaw(-0.01);
            }
        },
        {   sf::Keyboard::W, [this]() {
                pitch(0.01);
            }
        },
        {   sf::Keyboard::S, [this]() {
                pitch(-0.01);
            }
        },
        {   sf::Keyboard::Q, [this]() {
                roll(0.01);
            }
        },
        {   sf::Keyboard::E, [this]() {
                roll(-0.01);
            }
        },
        {   sf::Keyboard::Escape, [this]() {
                close();
            }
        },
    };
}

}
