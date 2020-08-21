#pragma once

#include "line.h"
#include "point.h"
#include "camera.h"
#include "frame.h"
#include "triangle.h"
#include "wire_object.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

class Camera;
class Frame;

class Screen {
public:
    constexpr static int kScreenSize = 1000;
    constexpr static Vector4d kAxis[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
    Screen();
    ~Screen();

    void update();
    void draw(sf::Vertex pixel);
    void draw(std::vector<sf::Vertex>& data);
    void draw(Line4d line);
    void draw(Triangle4d triangle);

    void add_object(WireObject* w) const;

    void move_camera(Vector4d v);
    void rotate_camera(double angle, int fixed_coord);
    void draw_axis();

    sf::RenderWindow window_;

private:
    Frame* frame_ = nullptr;
    Camera* camera_ = nullptr;
    sf::Vector2f center = sf::Vector2f(kScreenSize / 2, kScreenSize / 2);
};

}
