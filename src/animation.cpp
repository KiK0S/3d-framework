#include "animation.h"

Frame::Frame(sf::RenderWindow& window): window_(window) {}
void Frame::update() {
    window_.clear(sf::Color::White);
    const WireObject<double>& current = steps_[getStep()];
    for (auto& line3d : current.lines()) {
        Line2d line2d = camera_.projectLine(line3d);
        line2d.draw(window_);
    }
    camera_.draw_axis(window_);
    window_.display();
    frame_++;
}
void Frame::addObject(WireObject<>& t) {
    steps_.push_back(t);
}
void Frame::addCamera(Camera camera) {
    camera_ = camera;
}
int Frame::getStep() const { return (frame_ / FRAMES_PER_STEP) % steps_.size(); }
int Frame::getNextStep() const { return (getStep() + 1) % steps_.size(); }
