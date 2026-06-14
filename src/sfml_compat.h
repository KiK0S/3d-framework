#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstddef>

namespace app::sfml_compat {

#if SFML_VERSION_MAJOR >= 3

inline sf::VideoMode video_mode(std::size_t width, std::size_t height) {
    return sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)});
}

inline bool is_closed(const sf::Event& event) {
    return event.is<sf::Event::Closed>();
}

inline constexpr sf::Keyboard::Key key_left = sf::Keyboard::Key::Left;
inline constexpr sf::Keyboard::Key key_right = sf::Keyboard::Key::Right;
inline constexpr sf::Keyboard::Key key_down = sf::Keyboard::Key::Down;
inline constexpr sf::Keyboard::Key key_up = sf::Keyboard::Key::Up;
inline constexpr sf::Keyboard::Key key_z = sf::Keyboard::Key::Z;
inline constexpr sf::Keyboard::Key key_x = sf::Keyboard::Key::X;
inline constexpr sf::Keyboard::Key key_j = sf::Keyboard::Key::J;
inline constexpr sf::Keyboard::Key key_l = sf::Keyboard::Key::L;
inline constexpr sf::Keyboard::Key key_k = sf::Keyboard::Key::K;
inline constexpr sf::Keyboard::Key key_i = sf::Keyboard::Key::I;
inline constexpr sf::Keyboard::Key key_u = sf::Keyboard::Key::U;
inline constexpr sf::Keyboard::Key key_o = sf::Keyboard::Key::O;
inline constexpr sf::Keyboard::Key key_a = sf::Keyboard::Key::A;
inline constexpr sf::Keyboard::Key key_d = sf::Keyboard::Key::D;
inline constexpr sf::Keyboard::Key key_w = sf::Keyboard::Key::W;
inline constexpr sf::Keyboard::Key key_s = sf::Keyboard::Key::S;
inline constexpr sf::Keyboard::Key key_q = sf::Keyboard::Key::Q;
inline constexpr sf::Keyboard::Key key_e = sf::Keyboard::Key::E;
inline constexpr sf::Keyboard::Key key_space = sf::Keyboard::Key::Space;
inline constexpr sf::Keyboard::Key key_escape = sf::Keyboard::Key::Escape;

#else

inline sf::VideoMode video_mode(std::size_t width, std::size_t height) {
    return sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

inline bool is_closed(const sf::Event& event) {
    return event.type == sf::Event::Closed;
}

inline constexpr sf::Keyboard::Key key_left = sf::Keyboard::Left;
inline constexpr sf::Keyboard::Key key_right = sf::Keyboard::Right;
inline constexpr sf::Keyboard::Key key_down = sf::Keyboard::Down;
inline constexpr sf::Keyboard::Key key_up = sf::Keyboard::Up;
inline constexpr sf::Keyboard::Key key_z = sf::Keyboard::Z;
inline constexpr sf::Keyboard::Key key_x = sf::Keyboard::X;
inline constexpr sf::Keyboard::Key key_j = sf::Keyboard::J;
inline constexpr sf::Keyboard::Key key_l = sf::Keyboard::L;
inline constexpr sf::Keyboard::Key key_k = sf::Keyboard::K;
inline constexpr sf::Keyboard::Key key_i = sf::Keyboard::I;
inline constexpr sf::Keyboard::Key key_u = sf::Keyboard::U;
inline constexpr sf::Keyboard::Key key_o = sf::Keyboard::O;
inline constexpr sf::Keyboard::Key key_a = sf::Keyboard::A;
inline constexpr sf::Keyboard::Key key_d = sf::Keyboard::D;
inline constexpr sf::Keyboard::Key key_w = sf::Keyboard::W;
inline constexpr sf::Keyboard::Key key_s = sf::Keyboard::S;
inline constexpr sf::Keyboard::Key key_q = sf::Keyboard::Q;
inline constexpr sf::Keyboard::Key key_e = sf::Keyboard::E;
inline constexpr sf::Keyboard::Key key_space = sf::Keyboard::Space;
inline constexpr sf::Keyboard::Key key_escape = sf::Keyboard::Escape;

#endif

} // namespace app::sfml_compat
