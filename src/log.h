#pragma once

#include "point.h"
#include "matrix.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace app {

// TODO: spdlog

const bool DEBUG = true;

void debug(const std::string& s);
void debug(double d);
void debug(sf::Vector2f v);
void debug(Vector4d v);
void debug(const Matrix<4, 4>& mat);

}
