#include "matrix.h"
#include "renderer.h"
#include "triangle.h"
#include <vector>

namespace app {

Renderer::Renderer(double screen_width, double screen_height):
    screen_(screen_width, screen_height) {}

void Renderer::draw_frame(sf::RenderWindow& window) {
    draw_pixels(screen_.get_pixels_to_draw(), window);
    screen_.clear();
}

void Renderer::draw_triangle(const Camera& camera, const Triangle4d& triangle4d) {
    auto triangles_list = clip_triangle_camera_space(camera, triangle4d);
    for (auto clipped_triangle : triangles_list) {
        Triangle2d triangle2d = project_on_screen(camera, clipped_triangle);
        if (triangle2d.is_degenerate()) {
            return;
        }
        DrawData data = create_data(triangle2d, clipped_triangle);
        draw_data(camera, std::move(data));
    }
}

Matrix<2, 1> Renderer::get_coords(int x, int y, const Matrix2d& basis, sf::Vector2f left_point) {
    sf::Vector2f arrow = sf::Vector2f(x, y) - left_point;
    return basis.solve_system(Matrix<2, 1>(arrow));
}

double Renderer::get_z(const Camera& camera, int x, int y,
                       Matrix<2, 1>&& coords,
                       const Point4d& a, const Point4d& b, const Point4d& c) {
    Point4d p = a + coords(0, 0) * (b - a) + coords(1, 0) * (c - a);
    return camera.get_z_value(p);
}

std::optional<Point4d> Renderer::find_intersection(const Point4d& a,
        const Point4d& b,
        double z_plane) {
    bool a_side = a.z <= z_plane;
    bool b_side = b.z <= z_plane;
    if (a_side == b_side) {
        return {};
    }
    Vector4d v = b - a;
    Point4d nearest = a;
    if (a.z > b.z) {
        nearest = b;
        v *= -1;
    }
    return nearest + v * (z_plane - nearest.z) / v.z;
}

std::vector<Triangle4d> Renderer::divide_triangle(const Triangle4d& triangle,
        double z_plane,
        const Point4d& f_intersection,
        const Point4d& s_intersection) {
    Point4d base_split_point = triangle.a;
    assert((triangle.b - base_split_point).is_collinear(f_intersection - base_split_point));
    assert((triangle.c - base_split_point).is_collinear(s_intersection - base_split_point));
    if (base_split_point.z <= z_plane) return {
        Triangle4d(f_intersection, triangle.b, triangle.c, triangle.get_color()),
        Triangle4d(s_intersection, triangle.c, f_intersection, triangle.get_color())
    };
    if (base_split_point.z >= z_plane) return {
        Triangle4d(f_intersection, base_split_point, s_intersection, triangle.get_color())
    };
    assert(0);
    return {};
}

Triangle4d Renderer::move_triangle_to_another_basis(const Camera& camera, const Triangle4d& triangle) {
    Point4d A = camera.transform_to_cameras_coordinates(triangle.a);
    Point4d B = camera.transform_to_cameras_coordinates(triangle.b);
    Point4d C = camera.transform_to_cameras_coordinates(triangle.c);
    A.normalize();
    B.normalize();
    C.normalize();
    return Triangle4d(A, B, C, triangle.get_color());
}

Triangle2d Renderer::project_on_screen(const Camera& camera, const Triangle4d& triangle) {
    return Triangle2d(camera.project_on_screen(triangle.a),
                      camera.project_on_screen(triangle.b),
                      camera.project_on_screen(triangle.c));
}

double Renderer::get_scaled_z_value(double y, double top_y, double bottom_y, double top_z, double bottom_z) {
    if (top_z != bottom_z) {
        return top_z + (bottom_z - top_z) * (y - top_y) / (bottom_y - top_y);
    } else {
        return top_z;
    }
}

std::vector<Triangle4d> Renderer::clip_triangle_camera_space(const Camera& camera, const Triangle4d& triangle) {
    Triangle4d projected_triangle = move_triangle_to_another_basis(camera, triangle);
    Point4d A, B, C;
    std::tie(A, B, C) = std::tie(projected_triangle.a, projected_triangle.b, projected_triangle.c);
    double z_plane = camera.get_clipping_plane_distance();
    if (A.z <= z_plane &&
            B.z <= z_plane &&
            C.z <= z_plane) {
        return {};
    }
    std::optional<Point4d> cross_a = find_intersection(A, B, z_plane);
    std::optional<Point4d> cross_b = find_intersection(A, C, z_plane);
    std::optional<Point4d> cross_c = find_intersection(B, C, z_plane);
    std::optional<std::vector<Triangle4d>> intersection;
    if (cross_a && cross_b && !cross_c) {
        Triangle4d reordered_triangle{
            projected_triangle.a,
            projected_triangle.b,
            projected_triangle.c,
            projected_triangle.get_color()
        };
        return divide_triangle(reordered_triangle, z_plane,
                               *cross_a, *cross_b);
    }
    if (cross_a && cross_c && !cross_b) {
        Triangle4d reordered_triangle{
            projected_triangle.b,
            projected_triangle.a,
            projected_triangle.c,
            projected_triangle.get_color()
        };
        return divide_triangle(reordered_triangle, z_plane,
                               *cross_a, *cross_c);
    }
    if (cross_c && cross_b && !cross_a) {
        Triangle4d reordered_triangle{
            projected_triangle.c,
            projected_triangle.a,
            projected_triangle.b,
            projected_triangle.get_color()
        };
        return divide_triangle(reordered_triangle, z_plane,
                               *cross_b, *cross_c);
    }
    return {projected_triangle};
}

Renderer::DrawData Renderer::create_data(const Triangle2d& triangle2d, const Triangle4d& triangle4d) {
    Point4d a(0, 0, 0), b(0, 0, 0), c(0, 0, 0);
    std::array<int, 3> order = triangle2d.get_order();
    triangle4d.get_points(order, &a, &b, &c);

    sf::Vector2f left_point = triangle2d.get_left_point();
    sf::Vector2f right_point = triangle2d.get_right_point();
    Matrix2d basis = triangle2d.create_basis();
    return DrawData {
        a,
        b,
        c,
        left_point,
        right_point,
        std::move(basis),
        triangle2d,
        triangle4d.get_color()
    };
}

void Renderer::draw_data(const Camera& camera, const Renderer::DrawData& data) {
    int min_valid_x = std::max(0, (int)ceil(data.left_point.x));
    int max_valid_x = std::min((int)screen_.get_height() - 1, (int)floor(data.right_point.x));
    for (int x = min_valid_x; x <= max_valid_x; x++) {
        double top_y = data.triangle.min_y_in_line(x);
        double bottom_y = data.triangle.max_y_in_line(x);
        draw_line(x, top_y, bottom_y, camera, data);
    }
}

void Renderer::draw_line(int x, double top_y, double bottom_y,
                         const Camera& camera, const Renderer::DrawData& data) {
    double top_z = get_z(camera, x, top_y, std::move(get_coords(x, top_y, data.triangle_basis, data.left_point)), data.a, data.b, data.c);
    double bottom_z = get_z(camera, x, bottom_y, std::move(get_coords(x, bottom_y, data.triangle_basis, data.left_point)), data.a, data.b, data.c);
    int min_valid_y = std::max(0, (int)ceil(top_y));
    int max_valid_y = std::min((int)screen_.get_width() - 1, (int)floor(bottom_y));
    for (int y = min_valid_y; y <= max_valid_y; y++) {
        double z = get_scaled_z_value(y, top_y, bottom_y, top_z, bottom_z);
        screen_.set_pixel(x, y, z, data.color);
    }
}

void Renderer::draw_pixels(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) {
    window.draw(data.data(), data.size(), sf::Points);
}

}
