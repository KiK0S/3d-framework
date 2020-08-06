#pragma once

#include <SFML/Graphics.hpp> 
#include <vector>
#include "tetraedr.h"
#include "log.h"
#include "camera.h"

class Frame {
  public:
    Frame() = delete;
    Frame(sf::RenderWindow& window);
    void update();
    void addObject(WireObject<>& w);
    void addCamera(Camera camera);
    Camera camera_;
  private:
    int getStep() const ;
    int getNextStep() const ;
    std::vector<WireObject<>> steps_;
    sf::RenderWindow& window_;
    int frame_ = 0;
    const int FRAMES_PER_STEP = 50;
};