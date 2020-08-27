#include "screen.h"
#include <cassert>
#include <vector>

namespace app {

Screen::Screen(Renderer* renderer): renderer_(renderer), z_value_(renderer_->kScreenSize), color_(renderer_->kScreenSize) {
    assert(renderer_);
    for (int i = 0; i  < renderer_->kScreenSize; i++) {
        for (int j = 0; j < renderer_->kScreenSize; j++) {
            z_value_(i, j) = renderer_->get_max_z_value();
        }
    }
}

void Screen::update() {
    std::vector<sf::Vertex> data;
    data.reserve(renderer_->kScreenSize * renderer_->kScreenSize);
    for (int i = 0; i < renderer_->kScreenSize; i++) {
        for (int j = 0; j < renderer_->kScreenSize; j++) {
            if (z_value_(i, j) < renderer_->get_max_z_value()) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_(i, j)));
            }
        }
    }
    renderer_->draw(data);
    clear();
}

void Screen::clear() {
    for (int i = 0; i < renderer_->kScreenSize; i++) {
        for (int j = 0; j < renderer_->kScreenSize; j++) {
            color_(i, j) = sf::Color::White;
            z_value_(i, j) = renderer_->get_max_z_value();
        }
    }
}

void Screen::set_pixel(int x, int y, double z, sf::Color color) {
    if (x < 0 || y < 0 || x >= renderer_->kScreenSize || y >= renderer_->kScreenSize) {
        return;
    }
    if (z < z_value_(x, y)) {
        z_value_(x, y) = z;
        color_(x, y) = color;
    }
}

}
