#pragma once

#include "camera.h"
#include "world.h"
#include "line.h"
#include "point.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

class Screen;
class Camera;
class World;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void update();
    void draw(sf::Vertex pixel);
    void draw(std::vector<sf::Vertex>& data);
    void draw(Line4d line);
    void draw(Triangle4d triangle);

    void add_object(SurfaceObject* w) const;

    void move_camera(Vector4d v);
    void rotate_camera(double angle, int fixed_coord);
    void draw_axis();

    double get_max_z_value() const;

    constexpr static int kScreenSize = 1000;
    sf::RenderWindow window_;

private:
    Screen* screen_ = nullptr;
    World* world_ = nullptr;
    Camera* camera_ = nullptr;
    constexpr static Vector4d kAxis[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
    sf::Vector2f center = sf::Vector2f(kScreenSize / 2, kScreenSize / 2);
};

}
