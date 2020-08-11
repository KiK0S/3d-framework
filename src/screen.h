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
		const int SCREEN_SIZE = 1000;
		const Vector4d AXIS[3] = {Vector4d(100, 0, 0), Vector4d(0, 100, 0), Vector4d(0, 0, 100)};
      	const sf::Color COLORS[3] = {sf::Color::Green, sf::Color::Red, sf::Color::Blue};
		Screen();
		~Screen();
		
		void update() ;
	    void draw(sf::Vertex pixel);
	   	template <typename T>
		void draw(Line4d<T> line);

		void move_camera(Vector4d v);
    	void rotate_camera(double angle, int fixed_coord);
    	void draw_axis();

		Frame* frame_;
		Camera* camera_;
		sf::RenderWindow window_;
		sf::Vector2f center = sf::Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
	};
}