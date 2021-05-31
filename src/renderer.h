#pragma once

#include "camera.h"
#include "point.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

namespace app {

/*!
    \brief Класс рендерера
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Renderer {
public:
    /*!
        \brief Конструктор рендерера
     */
    Renderer(double width, double height, double max_z_value);

    /*!
        \brief Производит отрисовку кадра
     */
    void draw_frame(sf::RenderWindow& window);

    /*!
        \brief Добавляет треугольник на буферный кадр
     */
    void draw_triangle(const Camera& camera, const Triangle4d& triangle) ;

private:
    static double get_z(const Camera& camera, int x, int y, Matrix<2, 1>&& coords, const Point4d& a, const Point4d& b, const Point4d& c) ;
    static Matrix<2, 1> get_coords(int x, int y, const Matrix<2, 2>& basis, sf::Vector2f point) ;
    static std::optional<Point4d> find_intersection(const Point4d& a, const Point4d& b, double z) ;
    static std::vector<Triangle4d> divide_triangle(const Triangle4d& triangle, double z_plane,
                                                   const Point4d& f_intersection, const Point4d& s_intersection) ;
    static Triangle4d move_triangle_to_another_basis(const Camera& camera, const Triangle4d& triangle) ;
    static Triangle2d project_on_screen(const Camera& camera, const Triangle4d& triangle) ;
    static double get_scaled_z_value(double y, double top_y, double bottom_y, double top_z, double bottom_z) ;
    static std::vector<Triangle4d> clip_triangle_camera_space(const Camera& camera, const Triangle4d& triangle) ;


    struct DrawData {
        Point4d a;
        Point4d b;
        Point4d c;
        sf::Vector2f left_point;
        sf::Vector2f right_point;
        Matrix2d triangle_basis;
        Triangle2d triangle;
        sf::Color color;
    };
    static Renderer::DrawData create_data(const Triangle2d& triangle2d, const Triangle4d& triangle4d) ;

    void draw_data(const Camera& camera, const Renderer::DrawData& data);
    void draw_line(int x, double top_y, double bottom_y,
                   const Camera& camera, const Renderer::DrawData& data);
    void draw_pixels(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) ;

    Screen screen_;
};

}
