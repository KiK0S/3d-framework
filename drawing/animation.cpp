#include <SFML/Graphics.hpp> 
#include <vector>
#include "../objects/tetraedr.cpp"
#include "../logger/log.cpp"
#include "../camera/camera.cpp"

class Frame {
  public:
  	Frame() = delete;
  	Frame(sf::RenderWindow& window): window_(window) {}
  	void update() {
  		  window_.clear(sf::Color::White);
  		  Tetraedr<> current = steps_[getStep()];
        Tetraedr<> next =  steps_[getNextStep()];
        logger::debug("frame " + std::to_string(frame_));
        int frame_number = frame_ % FRAMES_PER_STEP;
        Tetraedr<> to_show = (frame_number * next + (FRAMES_PER_STEP - frame_number) * current) / FRAMES_PER_STEP;
        for (auto& line3d : to_show.lines()) {
            Line2d line2d = camera_.projectLine(line3d);
            line2d.draw(window_);
        }
        window_.display();
        frame_++;
  	}
  	void addObject(Tetraedr<> t) {
  	    steps_.push_back(t);
  	}
    void addCamera(Camera camera) {
       camera_ = camera;
    }
    Camera camera_;
  private:
  	std::vector<Tetraedr<>> steps_;
  	sf::RenderWindow& window_;
  	int frame_ = 0;
  	const int FRAMES_PER_STEP = 50;

  	int getStep() const { return (frame_ / FRAMES_PER_STEP) % steps_.size(); }
  	int getNextStep() const { return (getStep() + 1) % steps_.size(); }
};