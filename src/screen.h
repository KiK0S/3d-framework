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
    /*!
        \brief Конструктор экрана
    */
    Screen(size_t screen_width, size_t screen_height) ;

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

    /*!
        \brief возвращает ширину экрана
    */
    size_t get_width() const ;

    /*!
        \brief возвращает высоту экрана
    */
    size_t get_height() const ;

private:
    bool validate_pixel(int x, int y) const ;

    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;
};

}
