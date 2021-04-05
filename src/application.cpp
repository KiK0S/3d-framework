#include "application.h"
#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {


Application::Application(): world_(new World()), renderer_(new Renderer()) {}

Application::~Application() {
    delete world_;
    delete renderer_;
}

void Application::update() {
    debug("new frame");
    renderer_->prepare();
    int lines = 0;
    int triangles = 0;
    for (auto& object : *world_) {
        for (auto& line3d : object->lines()) {
            renderer_->draw(line3d);
            lines++;
        }
        for (auto& triangle : object->triangles()) {
            renderer_->draw(triangle);
            triangles++;
        }
    }
    renderer_->update();
    debug("/////////////");
}


void Application::move_camera(Vector4d v) const {
    renderer_->move_camera(v);
}

void Application::move_world(Vector4d v) const {
    // v = v;
    Matrix4d moving = Matrix4d::identity_matrix();
    moving(0, 3) = v.x;
    moving(1, 3) = v.y;
    moving(2, 3) = v.z;
    for (SurfaceObject* object : (*world_)) {
        for (Point4d& p : (*object)) {
            p = moving * p;
        }
    }
}

void Application::add_object(SurfaceObject* w) const {
    world_->add_object(w);
}


bool Application::poll_event(sf::Event& event) {
    return renderer_->poll_event(event);
}

bool Application::is_open() const {
    return renderer_->is_open();
}

void Application::close() {
    renderer_->close();
}

void Application::roll(double angle) const {
    renderer_->rotate_world(angle, 2);
}

void Application::pitch(double angle) const {
    renderer_->rotate_camera(angle, 1);
}

void Application::yaw(double angle) const {
    renderer_->rotate_camera(angle, 0);
}

void Application::elevation(double angle) const {
    renderer_->rotate_world(angle, 0);
}

void Application::azimuth(double angle) const {
    renderer_->rotate_world(angle, 1);
}

}
