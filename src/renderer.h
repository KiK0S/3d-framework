#pragma once

#include "camera.h"
#include "world.h"
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
class World;
class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void update();
    void draw(sf::Vertex pixel) ;
    void draw(const std::vector<sf::Vertex>& data) ;
    void draw(Line4d line) ;
    void draw(Triangle4d triangle) ;

    void add_object(SurfaceObject* w) const ;

    void move_camera(Vector4d v) const ;
    void move_world(Vector4d v) const ;
    void rotate_camera(double angle, int fixed_coord) const;
    void rotate_world(double angle, int fixed_coord) const;
    void draw_axis();

    double get_max_z_value() const ;
    size_t get_focus_distance() const ;
    size_t get_screen_size() const ;

    bool poll_event(sf::Event& event);
    bool is_open() const ;
    void close();

private:
    constexpr static size_t kScreenSize_ = 1000;
    sf::RenderWindow window_;
    Screen * const screen_ = nullptr;
    World * const world_ = nullptr;
    Camera * const camera_ = nullptr;
    constexpr static Vector4d kAxis_[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
    const static sf::Vector2f kCenter_;
};

}
