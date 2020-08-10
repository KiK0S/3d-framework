#include "screen.h"

namespace app {
	Screen::Screen(): frame_(new Frame(*this)), camera_(new Camera(*this)), window_(sf::VideoMode(1000, 1000), "Test 3: interacrtive camera") {}
	Screen::~Screen() {
		delete frame_;
		delete camera_;
	}
	void Screen::update() {
        window_.clear(sf::Color::White);
        frame_->update();
        camera_->draw_axis(window_);
        window_.display();
    }
    void Screen::draw(sf::Vertex pixel) {}
	void Screen::draw(Line2d line) {
		sf::RectangleShape shape(sf::Vector2f(line.length_, line.WIDTH));
        shape.setFillColor(line.color_);
        shape.setRotation(line.angle_);
        shape.setPosition(line.offset_ + center);
        window_.draw(shape);
	}
}