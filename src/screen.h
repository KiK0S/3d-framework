#pragma once

#include "pixel_screen.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

/*!
    \brief Класс экрана.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Screen {
public:
    Screen(size_t screen_width, size_t screen_height, double max_z_value);

    /*!
        \brief отобразить пиксель
    */
    void set_pixel(int x, int y, double z, sf::Color color);

    /*!
        \brief выбор всех пикслей
    */
    std::vector<sf::Vertex> get_picture();

    /*!
        \brief очистка
    */
    void clear();

private:
    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;
    size_t screen_width_;
    size_t screen_height_;
    double max_z_value_;
};

}
