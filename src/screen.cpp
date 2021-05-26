#include "screen.h"
#include <cassert>
#include <vector>

namespace app {

Screen::Screen(size_t screen_width, size_t screen_height, double max_z_value):
    z_value_(screen_width, screen_height, max_z_value),
    color_(screen_width, screen_height, sf::Color::Transparent),
    screen_width_(screen_width), screen_height_(screen_height) {}

std::vector<sf::Vertex> Screen::get_picture() {
    std::vector<sf::Vertex> data;
    data.reserve(screen_height_ * screen_width_);
    for (int i = 0; i < screen_width_; i++) {
        for (int j = 0; j < screen_height_; j++) {
            if (color_(i, j) != sf::Color::Transparent) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_(i, j)));
            }
        }
    }
    clear();
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
    if (z < z_value_(x, y)) {
        z_value_(x, y) = z;
        color_(x, y) = color;
    }
}

bool Screen::validate_pixel(int x, int y) {
    if (x < 0 || x >= screen_height_ ) {
        return false;
    }
    if (y < 0 || y >= screen_width_) {
        return false;
    }
    return true;
}


}
