#include "screen.h"
#include <cassert>
#include <vector>

namespace app {

Screen::Screen(size_t screen_width, size_t screen_height, double max_z_value):
    z_value_(screen_width, screen_height, max_z_value),
    color_(screen_width, screen_height, sf::Color::Transparent) {}

std::vector<sf::Vertex> Screen::get_pixels_to_draw() const {
    size_t screen_width = color_.get_width();
    size_t screen_height = color_.get_height();

    std::vector<sf::Vertex> data;
    data.reserve(screen_height * screen_width);

    for (int i = 0; i < screen_width; i++) {
        for (int j = 0; j < screen_height; j++) {
            if (color_(i, j) != sf::Color::Transparent) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_(i, j)));
            }
        }
    }
    return data;
}

void Screen::clear() {
    color_.clear();
    z_value_.clear();
}

void Screen::set_pixel(int x, int y, double z, sf::Color color) {
    if (!validate_pixel(x, y)) {
        return;
    }
    assert(z_value_.get_height() == color_.get_height());
    assert(z_value_.get_width() == color_.get_width());
    if (z < z_value_(x, y)) {
        z_value_(x, y) = z;
        color_(x, y) = color;
    }
}

bool Screen::validate_pixel(int x, int y) const {
    if (x < 0 || x >= color_.get_height()) {
        return false;
    }
    if (y < 0 || y >= color_.get_width()) {
        return false;
    }
    return true;
}

size_t Screen::get_height() const {
    return color_.get_height();
}

size_t Screen::get_width() const {
    return color_.get_width();
}


}
