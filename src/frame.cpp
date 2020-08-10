#include "frame.h"
#include "screen.h"
#include "wire_object.h"

namespace app {
    void Frame::update() {
        for (const auto& current : objects_) {
            for (auto& line3d : current.lines()) {
                Line2d line2d = screen_.camera_->projectLine(line3d);
                screen_.draw(line2d);
            }
        }
    }
    void Frame::addObject(WireObject<>& t) {
        objects_.push_back(t);
    }
}