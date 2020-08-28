#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

const sf::Vector2f Renderer::kCenter_ = sf::Vector2f(Renderer::kScreenSize_ / 2, Renderer::kScreenSize_ / 2);

Renderer::Renderer(): screen_(new Screen(this)), world_(new World(this)), camera_(new Camera(this)),
    window_(sf::VideoMode(kScreenSize_, kScreenSize_), "Test: interacrtive camera") {}

Renderer::~Renderer() {
    delete world_;
    delete camera_;
    delete screen_;
}

void Renderer::update() {
    window_.clear(sf::Color::White);
    camera_->create_transform();
    world_->update();
    screen_->update();
    draw_axis();
    window_.display();
}

void Renderer::draw(sf::Vertex pixel) {
    sf::Vertex data[] = {pixel};
    window_.draw(data, 1, sf::Points);
}

void Renderer::draw(const std::vector<sf::Vertex>& data) {
    const sf::Vertex* ptr = &data[0];
    window_.draw(ptr, data.size(), sf::Points);
}

void Renderer::draw(Triangle4d triangle) {
    Vector4d n = triangle.b - triangle.c;
    int raster_parameter_n = ceil(n.length() * 1.05);
    for (int i = 0; i <= raster_parameter_n; i++) {
        Vector4d p = triangle.c + n * (i * 1.0 / raster_parameter_n);
        draw(Line4d(triangle.a, p));
    }
}

void Renderer::draw(Line4d line4d) {
    Line2d line(camera_->project_point(line4d.start_) + kCenter_, camera_->project_point(line4d.finish_) + kCenter_);
    sf::RectangleShape rectangle(sf::Vector2f(line.length_, line.kWidth));
    rectangle.setRotation(line.angle_);
    rectangle.setPosition(line.offset_);
    rectangle.setFillColor(line.color_);
    window_.draw(rectangle);
}

void Renderer::move_camera(Vector4d v) const {
    v = camera_->get_world_transform() * v;
    Matrix4d moving = Matrix4d::identity_matrix();
    moving(0, 3) = v.x;
    moving(1, 3) = v.y;
    moving(2, 3) = v.z;
    camera_->apply_transform_to_camera(moving);
}

void Renderer::move_world(Vector4d v) const {
    v = v;
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

void Renderer::add_object(SurfaceObject* w) const {
    world_->add_object(w);
}

void Renderer::rotate_world(double angle, int fixed_coord) const {
    Matrix4d moving = Matrix4d::identity_matrix();
    moving((fixed_coord + 1) % 3, (fixed_coord + 1) % 3) = std::cos(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 2) % 3) = std::cos(angle);
    moving((fixed_coord + 1) % 3, (fixed_coord + 2) % 3) = std::sin(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 1) % 3) = -std::sin(angle);
    camera_->apply_transform_to_world(moving);
}

void Renderer::rotate_camera(double angle, int fixed_coord) const {
    move_camera(Vector4d(0, 0, -camera_->get_focus_distance()));
    rotate_world(angle, fixed_coord);
    move_camera(Vector4d(0, 0, camera_->get_focus_distance()));
}

void Renderer::draw_axis() {
    for (int i = 0; i < 3; i++) {
        draw(Line4d(Vector4d(0, 0, 0), kAxis_[i]));
    }
}

double Renderer::get_max_z_value() const {
    return camera_->get_max_z_value();
}

size_t Renderer::get_screen_size() const {
    return kScreenSize_;
}

bool Renderer::poll_event(sf::Event& event) {
    return window_.pollEvent(event);
}

bool Renderer::is_open() const {
    return window_.isOpen();
}

void Renderer::close() {
    window_.close();
}

}
