#include "frame.h"
#include "screen.h"
#include "wire_object.h"
#include "log.h"
#include "surface_object.h"
#include "triangle.h"
#include <string>
#include <vector>

namespace app {

Frame::Frame(Screen* screen):
    screen_(screen),
    color_(screen_->kScreenSize, std::vector<sf::Color>(screen_->kScreenSize)),
    z_value_(screen_->kScreenSize, std::vector<double>(screen_->kScreenSize, screen_->kScreenSize)) {}

void Frame::update() {
    for (auto current : objects_) {
        for (auto& line3d : current->lines()) {
            screen_->draw(line3d);
        }
        SurfaceObject* ptr = dynamic_cast<SurfaceObject*>(current);
        if (ptr != nullptr) {
            for (auto& triangle : ptr->triangles()) {
                screen_->draw(triangle);
            }
        }
    }
    std::vector<sf::Vertex> data;
    for (int i = 0; i < screen_->kScreenSize; i++) {
        for (int j = 0; j < screen_->kScreenSize; j++) {
            if (z_value_[i][j] < screen_->kScreenSize) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_[i][j]));
            }
        }
    }
    screen_->draw(data);
    clear();
}

void Frame::clear() {
    for (int i = 0; i < screen_->kScreenSize; i++) {
        for (int j = 0; j < screen_->kScreenSize; j++) {
            color_[i][j] = sf::Color::White;
            z_value_[i][j] = screen_->kScreenSize;
        }
    }
}

void Frame::add_object(WireObject* t) {
    objects_.push_back(t);
}

void Frame::set_pixel(int x, int y, double z, sf::Color color) {
    if (x < 0 || y < 0 || x >= screen_->kScreenSize || y >= screen_->kScreenSize) {
        return;
    }
    if (z < z_value_[x][y]) {
        z_value_[x][y] = z;
        color_[x][y] = color;
    }
}

std::vector<WireObject*>::iterator Frame::begin() {
    return objects_.begin();
}

std::vector<WireObject*>::iterator Frame::end() {
    return objects_.end();
}

}
