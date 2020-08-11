#include "screen.h"
#include "matrix.h"
#include "log.h"

namespace app {
	Screen::Screen(): frame_(new Frame(*this)), camera_(new Camera(*this)), window_(sf::VideoMode(1000, 1000), "Test 3: interacrtive camera") {}
	Screen::~Screen() {
		delete frame_;
		delete camera_;
	}
	void Screen::update() {
        window_.clear(sf::Color::White);
        frame_->update();
        draw_axis();
        window_.display();
    }
    void Screen::draw(sf::Vertex pixel) {
        sf::Vertex data[] = {pixel};
        window_.draw(data, 1, sf::Points);
    }
    template<typename T>
	void Screen::draw(Line4d<T> line) {
        Vector4d a = line.start_;
        Vector4d b = line.finish_ - line.start_;
        int raster_parameter = 1000;
        for (int i = 0; i <= raster_parameter; i++) {
            sf::Vector2f kek = camera_->projectPoint(a + b * i / raster_parameter) + center;
            int x = int(kek.x);
            int y = int(kek.y);
            // debug(std::to_string(x) + " " + std::to_string(y));
            if (x >= 0 && x < SCREEN_SIZE && y >= 0 && y < SCREEN_SIZE) {
                frame_->color_[x][y] = 1;
            }
        }
		// sf::RectangleShape shape(sf::Vector2f(line.length_, line.WIDTH));
  //       shape.setFillColor(line.color_);
  //       shape.setRotation(line.angle_);
  //       shape.setPosition(line.offset_ + center);
  //       window_.draw(shape);
	}
    void Screen::move_camera(Vector4d v) {
        Matrix4d moving;
        moving[0][0] = 1;
        moving[1][1] = 1;
        moving[2][2] = 1;
        moving[3][3] = 1;
        moving[0][3] = v.x;
        moving[1][3] = v.y;
        moving[2][3] = v.z;
        for (WireObject<>& wire_object : frame_->objects_) {
            for (Vector4d& vertex : wire_object) {
                vertex = moving * vertex;
            }
        }
    }
    void Screen::rotate_camera(double angle, int fixed_coord) {
        Matrix4d moving;
        moving[fixed_coord][fixed_coord] = 1;
        moving[(fixed_coord + 1) % 3][(fixed_coord + 1) % 3] = std::cos(angle);
        moving[(fixed_coord + 2) % 3][(fixed_coord + 2) % 3] = std::cos(angle);
        moving[(fixed_coord + 1) % 3][(fixed_coord + 2) % 3] = std::sin(angle);
        moving[(fixed_coord + 2) % 3][(fixed_coord + 1) % 3] = -std::sin(angle);
        moving[3][3] = 1;
        camera_->camera_ = moving * camera_->camera_;
        camera_->transform_ = moving * camera_->transform_;
    }
    void Screen::draw_axis() {
        for (int i = 0; i < 3; i++) {
            draw(camera_->projectLine(Line4d<double>(Vector4d(0, 0, 0), AXIS[i])));
        }
    }
}