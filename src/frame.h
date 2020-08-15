#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "classes.h"
#include "wire_object.h"
#include "surface_object.h"
#include "tetraedr.h"
#include "log.h"
#include "camera.h"
#include "screen.h"

namespace app {

class Frame {
public:
    Frame() = delete;
    Frame(Screen& screen);

    void update();
    void add_object(WireObject<>* w);

    void set_pixel(int x, int y, double z, sf::Color color);
    void clear();

    std::vector<WireObject<>*>::iterator begin();
    std::vector<WireObject<>*>::iterator end();

private:
    Screen& screen_;
    std::vector<std::vector<sf::Color>> color_;
    std::vector<std::vector<double>> z_value_;
    std::vector<WireObject<> *> objects_;
};

}
