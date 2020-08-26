#include "log.h"
#include <iostream>


namespace app {

void debug(const std::string& s) {
    if (!DEBUG) {
        return;
    }
    std::cerr << s << std::endl;
}

void debug(double d) {
    if (!DEBUG) {
        return;
    }
    std::cerr << d << std::endl;
}

void debug(sf::Vector2f v) {
    if (!DEBUG) {
        return;
    }
    std::cerr << v.x << ' ' << v.y << std::endl;
}

void debug(Vector4d v) {
    if (!DEBUG) {
        return;
    }
    std::cerr << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << std::endl;
}

}
