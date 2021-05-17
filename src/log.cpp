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
    std::cerr << v.x / v.w << ' ' << v.y / v.w << ' ' << v.z / v.w << ' ' << v.w << std::endl;
}

void debug(const Matrix4d& mat) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "[";
    for (int i = 0; i < 4; i++) {
        std::cerr << "[";
        for (int j = 0; j < 4; j++) {
            std::cerr << mat(i, j) << ',';
        }
        std::cerr << "], ";
    }
    std::cerr << "]\n";
}

}
