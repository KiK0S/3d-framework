#include "application.h"
#include "cube.h"
#include "point.h"
#include "tetraedr.h"
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    app::Application application;
    application.add_object(std::make_unique<app::Cube>(app::Point4d{0, 0, 100}, sf::Color::Red));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{0, 100, 100}, sf::Color::Yellow));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{100, 100, 100}, sf::Color::White));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{100, 0, 100}, sf::Color::Green));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{0, 0, 201}, sf::Color::Blue));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{0, 100, 201}, sf::Color::Black));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{100, 100, 201}, sf::Color::Magenta));
    application.add_object(std::make_unique<app::Cube>(app::Point4d{100, 0, 201}, sf::Color::Cyan));
    application.run();
    return 0;
}
