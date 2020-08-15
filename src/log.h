#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace app {

const bool DEBUG = true;

void debug(const std::string& s);
void debug(double d);
void debug(sf::Vector2f v);

}
