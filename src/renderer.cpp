#include "log.h"
#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

Renderer::Renderer(double screen_width, double screen_height, double max_z_value):
                                            screen_(screen_width, screen_height, max_z_value),
                                            screen_width_(screen_width),
                                            screen_height_(screen_height) {}

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

double Renderer::get_z(const Camera& camera, int x, int y, Matrix<2, 1>&& coords, Point4d& a, Point4d& b, Point4d& c) const {
    Point4d p = a + coords(0, 0) * (b - a) + coords(1, 0) * (c - a);
    return camera.get_z_value(p);
}

void Renderer::draw(const Camera& camera, const Triangle4d& triangle4d) {
    
    Triangle2d triangle2d(camera.project_point(triangle4d.a),
                          camera.project_point(triangle4d.b),
                          camera.project_point(triangle4d.c));
    debug(triangle2d.a);
    debug(triangle2d.b);
    debug(triangle2d.c);
    // debug(triangle4d.a);
    // debug(triangle4d.b);
    // debug(triangle4d.c);
    // debug(camera.transform_point(triangle4d.a));
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
    for (int x = std::max(0, (int)ceil(left_point.x)); x <= std::min((int)screen_width_, (int)floor(right_point.x)); x++) {
        min_y = triangle2d.min_y_in_line(x);
        max_y = triangle2d.max_y_in_line(x);

        double min_z = get_z(camera, x, min_y, std::move(get_coords(x, min_y, basis, left_point)), a, b, c);
        double max_z = get_z(camera, x, max_y, std::move(get_coords(x, max_y, basis, left_point)), a, b, c);
        for (int y = std::max(0, (int)ceil(min_y)); y <= std::min((int)screen_height_, (int)floor(max_y)); y++) {
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

void Renderer::draw(Line4d line4d, sf::RenderWindow& window, const Camera& camera) {
    Point4d A = camera.to_cameras_coordinates(line4d.start_);
    Point4d B = camera.to_cameras_coordinates(line4d.finish_);
    A.normalize();
    B.normalize();
    double z_plane = camera.kLeftPoint_.z * 0.01;
    if (A.z <= z_plane && B.z <= z_plane) {
        return;
    }
    if (A.z < z_plane || B.z < z_plane) {
        if (A.z > B.z) {
            std::swap(A, B);
        }
        Point4d dir = A - B;
        dir.resize(dir.length() * (B.z - z_plane) / (B.z - A.z));
        A = B + dir;
    }
    Line2d line(camera.project_point(A), camera.project_point(B));
    sf::RectangleShape rectangle(sf::Vector2f(line.length_, line.kWidth));
    rectangle.setRotation(line.angle_);
    rectangle.setPosition(line.offset_);
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
}

std::optional<Point4d> Renderer::find_intersection(Point4d a, Point4d b, double z) const{
    if (a.z <= z && b.z <= z) {
        return {};
    }
    if (a.z > z && b.z > z) {
        return {};
    }
    if (a.z > b.z) {
        std::swap(a, b);
    }
    Point4d v = b - a;
    return a + v * (z - a.z) / v.z;
}

std::vector<Triangle4d> Renderer::clip(const Camera& camera, const Triangle4d& triangle) const {
    Point4d A = camera.to_cameras_coordinates(triangle.a);
    Point4d B = camera.to_cameras_coordinates(triangle.b);
    Point4d C = camera.to_cameras_coordinates(triangle.c);
    double z_plane = camera.kLeftPoint_.z * 0.01;
    debug(A);
    debug(B);
    debug(C);
    A.normalize();
    B.normalize();
    C.normalize();
    if (A.z <= z_plane && B.z <= z_plane && C.z <= z_plane) {
        debug("triangle is too near");
        return {};
    }
    std::optional<Point4d> cross_a = find_intersection(A, B, z_plane);
    std::optional<Point4d> cross_b = find_intersection(A, C, z_plane);
    std::optional<Point4d> cross_c = find_intersection(B, C, z_plane);
    /*
        u need to visualise it
    */
    if (cross_a && cross_b && !cross_c) {
        debug ("changed A");
        if (A.z <= z_plane) return {
            Triangle4d(*cross_a, B, C),
            Triangle4d(*cross_b, C, *cross_a),
        };
        if (A.z >= z_plane) return {
            Triangle4d(*cross_a, A, *cross_b)
        };
    }
    if (cross_a && cross_c && !cross_b) {
        debug ("changed B");
        if (B.z <= z_plane) return {
            Triangle4d(*cross_a, A, C),
            Triangle4d(*cross_c, C, *cross_a),
        };
        if (B.z >= z_plane) return {
            Triangle4d(*cross_a, B, *cross_c)
        };
    }
    if (cross_c && cross_b && !cross_a) {
        debug ("changed C");
        if (C.z <= z_plane) return {
            Triangle4d(*cross_c, B, A),
            Triangle4d(*cross_b, A, *cross_c),
        };
        if (C.z >= z_plane) return {
            Triangle4d(*cross_c, C, *cross_b)
        };

    }
    debug ("nothing has changed");
    return {Triangle4d(A, B, C)};
}


}
