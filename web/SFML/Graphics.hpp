#pragma once

#include <cstddef>
#include <cstdint>

namespace sf {

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    constexpr Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    static const Color Black;
    static const Color Transparent;
    static const Color White;
};

inline constexpr Color Color::Black{0, 0, 0, 255};
inline constexpr Color Color::Transparent{0, 0, 0, 0};
inline constexpr Color Color::White{255, 255, 255, 255};

inline bool operator==(const Color& lhs, const Color& rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

inline bool operator!=(const Color& lhs, const Color& rhs) {
    return !(lhs == rhs);
}

struct Vector2f {
    float x;
    float y;

    constexpr Vector2f(float x_value = 0.0f, float y_value = 0.0f)
        : x(x_value), y(y_value) {}

    Vector2f& operator+=(const Vector2f& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2f& operator-=(const Vector2f& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2f& operator*=(float scale) {
        x *= scale;
        y *= scale;
        return *this;
    }
};

inline Vector2f operator+(Vector2f lhs, const Vector2f& rhs) {
    lhs += rhs;
    return lhs;
}

inline Vector2f operator-(Vector2f lhs, const Vector2f& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Vector2f operator*(Vector2f lhs, float scale) {
    lhs *= scale;
    return lhs;
}

inline bool operator==(const Vector2f& lhs, const Vector2f& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Vector2f& lhs, const Vector2f& rhs) {
    return !(lhs == rhs);
}

struct Vertex {
    Vector2f position;
    Color color;

    Vertex(Vector2f vertex_position = {}, Color vertex_color = {})
        : position(vertex_position), color(vertex_color) {}
};

enum PrimitiveType {
    Points
};

class VideoMode {
public:
    VideoMode(unsigned int = 0, unsigned int = 0) {}
};

struct Event {
    enum EventType {
        Closed
    };

    EventType type = Closed;
};

struct Keyboard {
    enum Key {
        Left,
        Right,
        Down,
        Up,
        Z,
        X,
        J,
        L,
        K,
        I,
        U,
        O,
        A,
        D,
        W,
        S,
        Q,
        E,
        Space,
        Escape
    };

    static bool isKeyPressed(Key) {
        return false;
    }
};

class RenderWindow {
public:
    void draw(const Vertex*, std::size_t, PrimitiveType) {}
};

} // namespace sf
