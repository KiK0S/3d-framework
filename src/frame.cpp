#include "frame.h"
#include "screen.h"
#include "wire_object.h"
#include "log.h"
#include "surface_object.h"
#include "triangle.h"
#include <string>
#include <vector>

namespace app {

Frame::Frame(Screen& screen): screen_(screen) {
    color_.assign(screen_.SCREEN_SIZE, std::vector<sf::Color>(screen_.SCREEN_SIZE));
    z_value_.assign(screen_.SCREEN_SIZE, std::vector<double>(screen_.SCREEN_SIZE, screen_.SCREEN_SIZE));
}

void Frame::update() {
    for (auto current : objects_) {
        for (auto& line3d : current->lines()) {
            screen_.draw(line3d);
        }
        SurfaceObject<double>* ptr = dynamic_cast<SurfaceObject<double>*>(current);
        if (ptr != nullptr) {
            for (auto& triangle : ptr->triangles()) {
                screen_.draw(triangle);
            }
        }
    }
    std::vector<sf::Vertex> data;
    for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
        for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
            if (z_value_[i][j] < screen_.SCREEN_SIZE) {
                data.push_back(sf::Vertex(sf::Vector2f(i, j), color_[i][j]));
            }
        }
    }
    screen_.draw(data);
    clear();
}

void Frame::clear() {
    for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
        for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
            color_[i][j] = sf::Color::White;
            z_value_[i][j] = screen_.SCREEN_SIZE;
        }
    }
}

void Frame::add_object(WireObject<>* t) {
    objects_.push_back(t);
}

void Frame::set_pixel(int x, int y, double z, sf::Color color) {
    if (x < 0 || y < 0 || x >= screen_.SCREEN_SIZE || y >= screen_.SCREEN_SIZE) {
        return;
    }
    if (z < z_value_[x][y]) {
        z_value_[x][y] = z;
        color_[x][y] = color;
    }
}

std::vector<WireObject<>*>::iterator Frame::begin() {
    return objects_.begin();
}

std::vector<WireObject<>*>::iterator Frame::end() {
    return objects_.end();
}

}
