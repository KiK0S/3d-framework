#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

Renderer::Renderer(): screen_(new Screen(this)), world_(new World(this)), camera_(new Camera(this)), window_(sf::VideoMode(1000, 1000), "Test: interacrtive camera") {}

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

void Renderer::draw(std::vector<sf::Vertex>& data) {
    sf::Vertex* ptr = &data[0];
    window_.draw(ptr, data.size(), sf::Points);
}

void Renderer::draw(Triangle4d triangle) {
    Vector4d n = triangle.b - triangle.a;
    Vector4d m = triangle.c - triangle.a;
    int raster_parameter_n = ceil(n.length() * 0.7);
    int raster_parameter_m = ceil(m.length() * 0.7);
    Triangle2d triangle2d(camera_->project_point(triangle.a) + center, camera_->project_point(triangle.b) + center, camera_->project_point(triangle.c) + center);
    for (int i = 0; i <= raster_parameter_n; i++) {
        for (int j = 0; j <= raster_parameter_m; j++) {
            Vector4d p = triangle.a + n * i / raster_parameter_n + m * j / raster_parameter_m;
            sf::Vector2f kek = camera_->project_point(p) + center;
            int x = round(kek.x);
            int y = round(kek.y);
            if (triangle2d.inner_point(x, y)) {
                screen_->set_pixel(x, y, camera_->get_z_value(p), sf::Color::Black);
            }
        }
    }
}

void Renderer::draw(Line4d line4d) {
    Line2d line(camera_->project_point(line4d.start_) + center, camera_->project_point(line4d.finish_) + center);
    sf::RectangleShape rectangle(sf::Vector2f(line.length_, line.kWidth));
    rectangle.setRotation(line.angle_);
    rectangle.setPosition(line.offset_);
    rectangle.setFillColor(line.color_);
    window_.draw(rectangle);
}

void Renderer::move_camera(Vector4d v) {
    v = camera_->get_world_transform() * v;
    Matrix4d moving = Matrix4d::identity_matrix();
    moving(0, 3) = v.x;
    moving(1, 3) = v.y;
    moving(2, 3) = v.z;
    camera_->apply_transform_to_camera(moving);
}

void Renderer::add_object(SurfaceObject* w) const {
    world_->add_object(w);
}

void Renderer::rotate_camera(double angle, int fixed_coord) {
    Matrix4d moving = Matrix4d::identity_matrix();
    moving((fixed_coord + 1) % 3, (fixed_coord + 1) % 3) = std::cos(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 2) % 3) = std::cos(angle);
    moving((fixed_coord + 1) % 3, (fixed_coord + 2) % 3) = std::sin(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 1) % 3) = -std::sin(angle);
    camera_->apply_transform_to_world(moving);
}

void Renderer::draw_axis() {
    for (int i = 0; i < 3; i++) {
        draw(Line4d(Vector4d(0, 0, 0), kAxis[i]));
    }
}

double Renderer::get_max_z_value() const {
    return camera_->get_max_z_value();
}

}
