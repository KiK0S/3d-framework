#include "frame.h"
#include "screen.h"
#include "wire_object.h"
#include "log.h"
#include <vector>

namespace app {

Frame::Frame(Screen& screen): screen_(screen) {
    color_.assign(screen_.SCREEN_SIZE, std::vector<bool>(screen_.SCREEN_SIZE));
}

void Frame::update() {
    for (const auto& current : objects_) {
        for (auto& line3d : current.lines()) {
            screen_.draw(line3d);
        }
    }
    std::vector<sf::Vertex> data;
    for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
        for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
            if (color_[i][j]) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), sf::Color::Black));
            }
        }
    }
    screen_.draw(data);
    clear();
}

void Frame::clear() {
    for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
        for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
            color_[i][j] = 0;
        }
    }
}

void Frame::add_object(WireObject<>& t) {
    objects_.push_back(t);
}

void Frame::set_pixel(int x, int y) {
    color_[x][y] = 1;
}

std::vector<WireObject<>>::iterator Frame::begin() {
    return objects_.begin();
}

std::vector<WireObject<>>::iterator Frame::end() {
    return objects_.end();
}

}
