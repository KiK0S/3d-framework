#include "log.h"
#include "screen.h"
#include <cassert>
#include <vector>

namespace app {

Screen::Screen(size_t screen_width, size_t screen_height, double max_z_value):
    z_value_(screen_width, screen_height), color_(screen_width, screen_height),
    max_z_value_(max_z_value), screen_width_(screen_width), screen_height_(screen_height) {
    for (int i = 0; i  < screen_width_; i++) {
        for (int j = 0; j < screen_height_; j++) {
            z_value_(i, j) = max_z_value_;
        }
    }
}

std::vector<sf::Vertex> Screen::get_picture() {
    // TODO: calc non-zero pixels
    std::vector<sf::Vertex> data;
    data.reserve(screen_height_ * screen_width_);
    for (int i = 0; i < screen_width_; i++) {
        for (int j = 0; j < screen_height_; j++) {
            if (z_value_(i, j) < max_z_value_) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_(i, j)));
            }
        }
    }
    clear();
    return data;
}

void Screen::clear() {
    for (int i = 0; i < screen_width_; i++) {
        for (int j = 0; j < screen_height_; j++) {
            color_(i, j) = sf::Color::White;
            z_value_(i, j) = max_z_value_;
        }
    }
}

void Screen::set_pixel(int x, int y, double z, sf::Color color) {
    if (x < 0 || y < 0 || x >= screen_height_ || y >= screen_width_ ||
            z > max_z_value_ || z < -max_z_value_) {
        return;
    }
    if (z < z_value_(x, y)) {
        z_value_(x, y) = z;
        color_(x, y) = color;
    }
}

}
