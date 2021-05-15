#pragma once

#include "pixel_screen.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

class Renderer;
/*!
    \brief Класс экрана.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Screen {
public:
    Screen(Renderer* renderer);

/*!
    \brief отобразить пиксель
*/  
    void set_pixel(int x, int y, double z, sf::Color color);
    void update();
/*!
    \brief выбор всех пикслей
*/

/*!
    \brief очистка
*/  
    void clear();

private:
    Renderer * const renderer_ = nullptr;
    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;

};

}
