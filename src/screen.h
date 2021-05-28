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
    Screen(size_t screen_width, size_t screen_height, double max_z_value) ;

    /*!
        \brief отобразить пиксель
    */
    void set_pixel(int x, int y, double z, sf::Color color) ;

    /*!
        \brief выбор всех пикслей
    */
    std::vector<sf::Vertex> get_pixels_to_draw() const ;

    /*!
        \brief очистка
    */
    void clear() ;

    bool validate_pixel(int x, int y) const ;

    size_t get_width() const ;

    size_t get_height() const ;

private:

    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;
};

}
