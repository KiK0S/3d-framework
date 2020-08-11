#include "frame.h"
#include "screen.h"
#include "wire_object.h"
#include "log.h"

namespace app {
    Frame::Frame(Screen& screen): screen_(screen) {
        color_.assign(screen_.SCREEN_SIZE, std::vector<bool>(screen_.SCREEN_SIZE));
    }
    void Frame::update() {
        for (const auto& current : objects_) {
            for (auto& line3d : current.lines()) {
                Line4d<double> line2d = screen_.camera_->projectLine(line3d);
                screen_.draw(line2d);
            }
        }
        for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
            for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
                if (color_[i][j]) {
                    screen_.draw(sf::Vertex(sf::Vector2f(i, j), sf::Color::Black));
                }
            }
        }
        for (int i = 0; i < screen_.SCREEN_SIZE; i++) {
            for (int j = 0; j < screen_.SCREEN_SIZE; j++) {
                color_[i][j] = 0;
            }
        }
    }
    void Frame::addObject(WireObject<>& t) {
        objects_.push_back(t);
    }
}