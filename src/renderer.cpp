#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

const sf::Vector2f Renderer::kCenter_ = sf::Vector2f(Renderer::kScreenSize_ / 2, Renderer::kScreenSize_ / 2);
const Vector4d Renderer::kAxis_[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};

Renderer::Renderer(): screen_(Renderer::kScreenSize_, 1000), camera_() {}

void Renderer::prepare() {
    camera_.create_transform();
}

void Renderer::update(sf::RenderWindow& window) {
    draw(screen_.get_picture(), window);
}

void Renderer::draw(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) {
    const sf::Vertex* ptr = &data[0];
    window.draw(ptr, data.size(), sf::Points);
}

Matrix<2, 1> Renderer::get_coords(int x, int y, Matrix<2, 2>& basis, sf::Vector2f& left_point) const {
    sf::Vector2f arrow = sf::Vector2f(x, y) - left_point;
    return basis.solve_system(Matrix<1, 2>({arrow}).transpose());  
}

double Renderer::get_z(int x, int y, Matrix<2, 1>&& coords, Point4d& a, Point4d& b, Point4d& c) const {
    Point4d p = a + coords(0, 0) * (b - a) + coords(1, 0) * (c - a);
    return camera_.get_z_value(p);
}

void Renderer::draw(const Triangle4d& triangle4d) {
    
    Triangle2d triangle2d(camera_.project_point(triangle4d.a),
                          camera_.project_point(triangle4d.b),
                          camera_.project_point(triangle4d.c));
    
    // debug(triangle2d.a);
    // debug(triangle2d.b);
    // debug(triangle2d.c);
    debug(triangle4d.a);
    debug(triangle4d.b);
    debug(triangle4d.c);
    debug(camera_.transform_point(triangle4d.a));
    debug("---");

    if (triangle2d.a == triangle2d.b || triangle2d.c == triangle2d.a || triangle2d.c == triangle2d.b) {
        return;
    }
    std::array<int, 3> order = triangle2d.get_order();
    Point4d a(0, 0, 0), b(0, 0, 0), c(0, 0, 0);
    triangle4d.sort_points(order, a, b, c);
    sf::Vector2f left_point = triangle2d.get_left_point();
    sf::Vector2f right_point = triangle2d.get_right_point();
    double min_y;
    double max_y;
    Matrix<2, 2> basis = triangle2d.create_basis();
    for (int x = ceil(left_point.x); x <= floor(right_point.x); x++) {
        min_y = find_min_y(triangle2d, x);
        max_y = find_max_y(triangle2d, x);

        double min_z = get_z(x, min_y, std::move(get_coords(x, min_y, basis, left_point)), a, b, c);
        double max_z = get_z(x, max_y, std::move(get_coords(x, max_y, basis, left_point)), a, b, c);
        for (int y = ceil(min_y); y <= floor(max_y); y++) {
            // if (!triangle2d.inner_point(sf::Vector2f(x, y))) {
            //     continue;
            // }   
            // 
            double z = 0;
            if (min_z != max_z) {
                z = (max_z - min_z) * (y - min_y) / (max_y - min_y);
            } else {
                z = max_z;
            }
            screen_.set_pixel(x, y, z, sf::Color::Black);
        }
    }
}

void Renderer::draw(Line4d line4d, sf::RenderWindow& window) {
    Line2d line(camera_.project_point(line4d.start_), camera_.project_point(line4d.finish_));
    sf::RectangleShape rectangle(sf::Vector2f(line.length_, line.kWidth));
    rectangle.setRotation(line.angle_);
    rectangle.setPosition(line.offset_);
    rectangle.setFillColor(line.color_);
    window.draw(rectangle);
}

void Renderer::move_camera(Vector4d v) {
    camera_.move(v);
}

void Renderer::rotate_world(double angle, int fixed_coord) {
    Matrix4d moving = Matrix4d::identity_matrix();
    moving((fixed_coord + 1) % 3, (fixed_coord + 1) % 3) = std::cos(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 2) % 3) = std::cos(angle);
    moving((fixed_coord + 1) % 3, (fixed_coord + 2) % 3) = std::sin(angle);
    moving((fixed_coord + 2) % 3, (fixed_coord + 1) % 3) = -std::sin(angle);
    camera_.apply_transform_to_world(moving);
}

void Renderer::rotate_camera(double angle, int fixed_coord) {
    // move_camera(Vector4d(0, 0, -camera_.get_focus_distance()));
    rotate_world(angle, fixed_coord);
    // move_camera(Vector4d(0, 0, camera_.get_focus_distance()));
}

double Renderer::get_max_z_value() const {
    return camera_.get_max_z_value();
}

double Renderer::get_min_z_value() const {
    return camera_.get_min_z_value();
}

size_t Renderer::get_screen_size() const {
    return kScreenSize_;
}

void Renderer::roll(double angle) {
    rotate_world(angle, 2);
}

void Renderer::pitch(double angle) {
    rotate_camera(angle, 1);
}

void Renderer::yaw(double angle) {
    rotate_camera(angle, 0);
}

void Renderer::elevation(double angle) {
    rotate_world(angle, 0);
}

void Renderer::azimuth(double angle) {
    rotate_world(angle, 1);
}

double Renderer::find_min_y(const Triangle2d& triangle, double x) const {
    if (std::abs(triangle.b.x - x) < 1e-10) {
        return triangle.b.y;
    }
    if (triangle.b.x > x) {
        sf::Vector2f v = triangle.a - triangle.b;
        if (std::abs(v.x) < 1e-5) {
            return triangle.a.y;   
        }
        double k = (triangle.b.x - x) / v.x;
        v *= std::abs(k);
        return (triangle.b + v).y;
    }
    else {
        sf::Vector2f v = triangle.c - triangle.b;
        if (std::abs(v.x) < 1e-5) {
            return triangle.b.y;
        }
        double k = (triangle.b.x - x) / v.x;
        v *= std::abs(k);
        return (triangle.b + v).y;
    }
}

double Renderer::find_max_y(const Triangle2d& triangle, double x) const {
    if (std::abs(triangle.c.x - x) < 1e-10) {
        return triangle.c.y;
    }
    if (triangle.c.x > x) {
        sf::Vector2f v = triangle.a - triangle.c;
       if (std::abs(v.x) < 1e-5) {
            return triangle.c.y;
        }
        double k = (triangle.c.x - x) / v.x;
        v *= std::abs(k);
        return (triangle.c + v).y;
    }
    else {
        sf::Vector2f v = triangle.b - triangle.c;
        if (std::abs(v.x) < 1e-5) {
            return triangle.c.y;
        }
        double k = (triangle.c.x - x) / v.x;
        v *= std::abs(k);
        return (triangle.c + v).y;
    }
}

}
