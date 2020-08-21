#include "screen.h"
#include "matrix.h"
#include "log.h"
#include "triangle.h"
#include <vector>

namespace app {

Screen::Screen(): frame_(new Frame(this)), camera_(new Camera(this)), window_(sf::VideoMode(1000, 1000), "Test: interacrtive camera") {}

Screen::~Screen() {
    delete frame_;
    delete camera_;
}

void Screen::update() {
    window_.clear(sf::Color::White);
    frame_->update();
    draw_axis();
    window_.display();
}

void Screen::draw(sf::Vertex pixel) {
    sf::Vertex data[] = {pixel};
    window_.draw(data, 1, sf::Points);
}

void Screen::draw(std::vector<sf::Vertex>& data) {
    sf::Vertex* ptr = &data[0];
    window_.draw(ptr, data.size(), sf::Points);
}

void Screen::draw(Triangle4d triangle) {
    Vector4d n = triangle.b - triangle.a;
    Vector4d m = triangle.c - triangle.a;
    int raster_parameter_n = ceil(n.length() * 0.9);
    int raster_parameter_m = ceil(m.length() * 0.9);
    Triangle2d triangle2d(camera_->project_point(triangle.a) + center, camera_->project_point(triangle.b) + center, camera_->project_point(triangle.c) + center);
    for (int i = 0; i <= raster_parameter_n; i++) {
        for (int j = 0; j <= raster_parameter_m; j++) {
            Vector4d p = triangle.a + n * i / raster_parameter_n + m * j / raster_parameter_m;
            sf::Vector2f kek = camera_->project_point(p) + center;
            int x = round(kek.x);
            int y = round(kek.y);
            if (triangle2d.inner_point(x, y)) {
                frame_->set_pixel(x, y, camera_->get_z_value(p), sf::Color::Black);
            }
        }
    }
}

void Screen::draw(Line4d line) {
    Vector4d a = line.start_;
    Vector4d b = line.finish_ - line.start_;
    int raster_parameter = ceil(b.length() * 1.05);
    for (int i = 0; i <= raster_parameter; i++) {
        Vector4d m = a + b * i / raster_parameter;
        sf::Vector2f kek = camera_->project_point(m) + center;
        int x = round(kek.x);
        int y = round(kek.y);
        frame_->set_pixel(x, y, camera_->get_z_value(m), sf::Color::Red);
    }
}

void Screen::move_camera(Vector4d v) {
    v = camera_->find_inverse_transform() * v;
    Matrix4d moving = Matrix4d::identity_matrix();
    moving(0, 3) = v.x;
    moving(1, 3) = v.y;
    moving(2, 3) = v.z;
    for (WireObject* wire_object : *frame_) {
        for (Vector4d& vertex : *wire_object) {
            vertex = moving * vertex;
        }
    }
}

void Screen::add_object(WireObject* w) const {
    frame_->add_object(w);
}

void Screen::rotate_camera(double angle, int fixed_coord) {
    Matrix4d moving;
    moving(fixed_coord, fixed_coord) = 1;
    moving((fixed_coord + 1) % 3, (fixed_coord + 1) % 3) = std::cos(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 2) % 3) = std::cos(angle);
    moving((fixed_coord + 1) % 3, (fixed_coord + 2) % 3) = std::sin(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 1) % 3) = -std::sin(angle);
    moving(3, 3) = 1;
    camera_->apply_matrix(moving);
}

void Screen::draw_axis() {
    for (int i = 0; i < 3; i++) {
        draw(Line4d(Vector4d(0, 0, 0), kAxis[i]));
    }
}

}
