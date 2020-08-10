#pragma once

#include "classes.h"
#include "line.h"
#include "point.h"
#include "camera.h"
#include "frame.h"
#include <SFML/Graphics.hpp>

namespace app {
	class Screen {
	  public:
		Screen();
		~Screen();
		void update() ;
	    void draw(sf::Vertex pixel);
		void draw(Line2d line);
		Frame* frame_;
		Camera* camera_;
		sf::RenderWindow window_;
		const int SCREEN_SIZE = 1000;
		sf::Vector2f center = sf::Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
	};
}