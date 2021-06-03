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
    application.get_world().add_object(std::make_unique<app::Cube>(app::Point4d{0, 0, 50}, sf::Color::Black));
    application.run();
    return 0;
}
