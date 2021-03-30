#pragma once

#include "renderer.h"
#include "world.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

namespace app {

/*!
    \brief Дочерний класс
    \author Norserium
    \version 1.0
    \date Март 2015 года
    \warning Данный класс создан только в учебных целях

    Обычный дочерний класс, который отнаследован от ранее созданного класса Parent
*/
class Application {
public:
    Application();
    ~Application();

    void update();
    
    void add_object(SurfaceObject* w) const ;

    void move_camera(Vector4d v) const ;
    void move_world(Vector4d v) const ;
    
    void pitch(double angle) const ;
    void roll(double angle) const ;
    void elevation(double angle) const ;
    void azimuth(double angle) const ;
    void yaw(double angle) const ;

    bool poll_event(sf::Event& event);
    bool is_open() const ;
    void close(); ;
private:
    sf::RenderWindow window_;
    Renderer * const renderer_;
    World * const world_;
};

}
