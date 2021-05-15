#include "application.h"
#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application(): world_(), renderer_() {}

void Application::update() {
    debug("new frame");
    renderer_.prepare();
    int lines = 0;
    int triangles = 0;
    for (auto& object : world_) {
        for (auto& triangle : object->triangles()) {
            renderer_.draw(triangle);
            triangles++;
        }
        for (auto& line3d : object->lines()) {
            renderer_.draw(line3d);
            lines++;
        }
    }
    renderer_.update();
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

void Application::add_object(SurfaceObject* w) {
    world_.add_object(w);
}

bool Application::poll_event(sf::Event& event) {
    return renderer_.poll_event(event);
}

bool Application::is_open() const {
    return renderer_.is_open();
}

void Application::close() {
    renderer_.close();
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

}
