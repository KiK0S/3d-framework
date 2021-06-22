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
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{0, 0, 50}, sf::Color::Red));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{0, 50, 50}, sf::Color::Yellow));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{50, 50, 50}, sf::Color::Red));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{50, 0, 50}, sf::Color::Green));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{0, 0, 101}, sf::Color::Blue));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{0, 50, 101}, sf::Color::Black));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{50, 50, 101}, sf::Color::Magenta));
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{50, 0, 101}, sf::Color::Cyan));
    application.run();
    return 0;
}
