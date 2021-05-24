#pragma once

#include "camera.h"
#include "line.h"
#include "point.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

namespace app {

class Screen;
class Camera;

/*!
    \brief Класс рендерера
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Renderer {
public:
    Renderer(double width, double height, double max_z_value);

    void update(sf::RenderWindow& window);
    void draw(sf::Vertex pixel) ;
    void draw(const std::vector<sf::Vertex>& data, sf::RenderWindow& window) ;
    void draw(Line4d line, sf::RenderWindow& window, const Camera& camera) ;
    void draw(const Camera& camera, const Triangle4d& triangle) ;

    std::vector<Triangle4d> clip(const Camera& camera, const Triangle4d& triangle) const ;

    double get_z(const Camera& camera, int x, int y, Matrix<2, 1>&& coords, Point4d& a, Point4d& b, Point4d& c) const ;
    Matrix<2, 1> get_coords(int x, int y, Matrix<2, 2>& basis, sf::Vector2f& point) const ;


    std::optional<Point4d> find_intersection(Point4d a, Point4d b, double z) const ;

private:
    Screen screen_;
    const unsigned int screen_width_, screen_height_;
};

}
