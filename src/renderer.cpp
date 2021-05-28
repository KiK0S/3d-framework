#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

Renderer::Renderer(double screen_width, double screen_height, double max_z_value):
                   screen_(screen_width, screen_height, max_z_value) {}

void Renderer::draw_frame(sf::RenderWindow& window) {
    draw(screen_.get_pixels_to_draw(), window);
    screen_.clear();
}

void Renderer::draw(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) {
    window.draw(data.data(), data.size(), sf::Points);
}

void Renderer::draw_triangle(const Camera& camera, const Triangle4d& triangle4d) {

    Triangle2d triangle2d(camera.project_on_screen(triangle4d.a),
                          camera.project_on_screen(triangle4d.b),
                          camera.project_on_screen(triangle4d.c));
    if (triangle2d.is_degenerate()) {
        return;
    }
    std::array<int, 3> order = triangle2d.get_order();
    Point4d a(0, 0, 0), b(0, 0, 0), c(0, 0, 0);
    triangle4d.assign_points(order, a, b, c);
    sf::Vector2f left_point = triangle2d.get_left_point();
    sf::Vector2f right_point = triangle2d.get_right_point();
    double min_y;
    double max_y;
    Matrix<2, 2> basis = triangle2d.create_basis();
    for (int x = ceil(left_point.x); x <= floor(right_point.x); x++) {
        if (x < 0 || x >= screen_.get_height()) {
            continue;
        }
        min_y = triangle2d.min_y_in_line(x);
        max_y = triangle2d.max_y_in_line(x);
        double min_z = get_z(camera, x, min_y, std::move(get_coords(x, min_y, basis, left_point)), a, b, c);
        double max_z = get_z(camera, x, max_y, std::move(get_coords(x, max_y, basis, left_point)), a, b, c);
        for (int y = ceil(min_y); y <= floor(max_y); y++) {
            if (y < 0 || y >= screen_.get_width()) {
                continue;
            }
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

std::vector<Triangle4d> Renderer::clip_triangle(const Camera& camera, const Triangle4d& triangle) const {
    Point4d A = camera.transform_to_cameras_coordinates(triangle.a);
    Point4d B = camera.transform_to_cameras_coordinates(triangle.b);
    Point4d C = camera.transform_to_cameras_coordinates(triangle.c);
    double z_plane = camera.get_clipping_plane_distance();
    A.normalize();
    B.normalize();
    C.normalize();
    if (A.z <= z_plane && B.z <= z_plane && C.z <= z_plane) {
        return {};
    }
    std::optional<Point4d> cross_a = find_intersection(A, B, z_plane);
    std::optional<Point4d> cross_b = find_intersection(A, C, z_plane);
    std::optional<Point4d> cross_c = find_intersection(B, C, z_plane);
    std::optional<std::vector<Triangle4d>> intersection;
    if (cross_a && cross_b && !cross_c) {
        return divide_triangle(A, B, C, z_plane,
                               *cross_a, *cross_b);
    }
    if (cross_a && cross_c && !cross_b) {
        return divide_triangle(B, A, C, z_plane,
                       *cross_a, *cross_c);
    }
    if (cross_c && cross_b && !cross_a) {
        return divide_triangle(C, A, B, z_plane,
                       *cross_b, *cross_c);
    }
    return {Triangle4d(A, B, C)};
}

Matrix<2, 1> Renderer::get_coords(int x, int y, Matrix<2, 2>& basis, sf::Vector2f& left_point) {
    sf::Vector2f arrow = sf::Vector2f(x, y) - left_point;
    return basis.solve_system(Matrix<1, 2>({arrow}).transpose());
}

double Renderer::get_z(const Camera& camera, int x, int y,
                       Matrix<2, 1>&& coords,
                       Point4d& a, Point4d& b, Point4d& c) {
    Point4d p = a + coords(0, 0) * (b - a) + coords(1, 0) * (c - a);
    return camera.get_z_value(p);
}

std::optional<Point4d> Renderer::find_intersection(const Point4d& a,
                                                   const Point4d& b,
                                                   double z) {
    if (a.z <= z && b.z <= z) {
        return {};
    }
    if (a.z > z && b.z > z) {
        return {};
    }
    Vector4d v = b - a;
    Point4d nearest = a;
    if (a.z > b.z) {
        nearest = b;
        v *= -1;
    }
    return nearest + v * (z - nearest.z) / v.z;
}

std::vector<Triangle4d> Renderer::divide_triangle(const Point4d& base_split_point,
                                                  const Point4d& A, const Point4d& B,
                                                  double z_plane,
                                                  const Point4d& f_intersection,
                                                  const Point4d& s_intersection) {
    assert((A - base_split_point).is_collinear(f_intersection - base_split_point));
    assert((B - base_split_point).is_collinear(s_intersection - base_split_point));
    if (base_split_point.z <= z_plane) return {
        Triangle4d(f_intersection, A, B),
        Triangle4d(s_intersection, B, f_intersection),
    };
    if (base_split_point.z >= z_plane) return {
        Triangle4d(f_intersection, base_split_point, s_intersection)
    };
    assert(0);
    return {};
}


}
