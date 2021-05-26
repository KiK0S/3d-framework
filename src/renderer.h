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
    Renderer(double width, double height, double max_z_value);

    void draw_frame(sf::RenderWindow& window);
    void draw(sf::Vertex pixel) ;
    void draw(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) ;
    std::vector<Triangle4d> clip_triangle(const Camera& camera, const Triangle4d& triangle) const ;
    void draw_triangle(const Camera& camera, const Triangle4d& triangle) ;

private:
    static double get_z(const Camera& camera, int x, int y, Matrix<2, 1>&& coords, Point4d& a, Point4d& b, Point4d& c) ;
    static Matrix<2, 1> get_coords(int x, int y, Matrix<2, 2>& basis, sf::Vector2f& point) ;
    static std::optional<Point4d> find_intersection(const Point4d& a, const Point4d& b, double z) ;
    static std::vector<Triangle4d> divide_triangle(const Point4d& base_split_point, const Point4d& A, const Point4d& B,
                    double z_plane, const Point4d& f_intersection, const Point4d& s_intersection) ;
    Screen screen_;
    const unsigned int screen_width_, screen_height_;
};

}
