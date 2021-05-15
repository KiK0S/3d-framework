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
    Renderer();

    void update();
    void prepare();
    void draw(sf::Vertex pixel) ;
    void draw(const std::vector<sf::Vertex>& data) ;
    void draw(Line4d line) ;
    void draw(const Triangle4d& triangle) ;

    void add_object(SurfaceObject* w) ;

    void move_camera(Vector4d v) ;
    void move_world(Vector4d v) ;
    
    void pitch(double angle) ;
    void roll(double angle) ;
    void elevation(double angle) ;
    void azimuth(double angle) ;
    void yaw(double angle) ;

    void rotate_camera(double angle, int fixed_coord) ;
    void rotate_world(double angle, int fixed_coord) ;
    void draw_axis();

    double get_max_z_value() const ;
    double get_min_z_value() const ;
    size_t get_focus_distance() const ;
    size_t get_screen_size() const ;

    bool poll_event(sf::Event& event);
    bool is_open() const ;
    void close();

    double find_max_y(const Triangle2d& triangle, double x) const ;
    double find_min_y(const Triangle2d& triangle, double x) const ;

    double get_z(int x, int y, Matrix<2, 1>&& coords, Point4d& a, Point4d& b, Point4d& c) const ;
    Matrix<2, 1> get_coords(int x, int y, Matrix<2, 2>& basis, sf::Vector2f& point) const ;
private:
    constexpr static size_t kScreenSize_ = 1000;
    sf::RenderWindow window_;
    Screen screen_;
    Camera camera_;
    const static Vector4d kAxis_[3];
    const static sf::Vector2f kCenter_;

};

}
