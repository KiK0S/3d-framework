#include "log.h"
#include <iostream>


namespace app {

void debug(const std::string& s) {
    if (!PRINT) {
        return;
    }
    std::cout << s << '\n';
    if (FLUSH) {
        std::cout.flush();
    }
}

void debug(double d) {
    if (!PRINT) {
        return;
    }
    std::cout << d << '\n';
    if (FLUSH) {
        std::cout.flush();
    }
}


void debug(sf::Vector2f v) {
    if (!PRINT) {
        return;
    }
    std::cout << v.x << ' ' << v.y << '\n';
    if (FLUSH) {
        std::cout.flush();
    }
}


void debug(Vector4d v) {
    if (!PRINT) {
        return;
    }
    std::cout << v.x / v.w << ' ' << v.y / v.w << ' ' << v.z / v.w << ' ' << v.w << '\n';
    if (FLUSH) {
        std::cout.flush();
    }
}


void debug(const Matrix4d& mat) {
    if (!PRINT) {
        return;
    }
    std::cout << "[";
    for (int i = 0; i < 4; i++) {
        std::cout << "[";
        for (int j = 0; j < 4; j++) {
            std::cout << mat(i, j) << ',';
        }
        std::cout << "], ";
    }
    std::cout << "]\n";
    if (FLUSH) {
        std::cout.flush();
    }
}

}
