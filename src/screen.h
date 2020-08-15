#pragma once

#include "classes.h"
#include "line.h"
#include "point.h"
#include "camera.h"
#include "frame.h"
#include "triangle.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

class Screen {
public:
    const int SCREEN_SIZE = 1000;
    const Vector4d AXIS[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
    const sf::Color COLORS[3] = {sf::Color::Green, sf::Color::Red, sf::Color::Blue};
    Screen();
    ~Screen();

    void update() ;
    void draw(sf::Vertex pixel);
    void draw(std::vector<sf::Vertex>& data);
    template <typename T>
    void draw(Line4d<T> line);
    template <typename T>
    void draw(Triangle4d<T> triangle);

    void add_object(WireObject<>* w) const;

    void move_camera(Vector4d v);
    void rotate_camera(double angle, int fixed_coord);
    void draw_axis();

    sf::RenderWindow window_;

private:
    Frame* frame_;
    Camera* camera_;
    sf::Vector2f center = sf::Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
};

}
