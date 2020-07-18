#include <SFML/Graphics.hpp>
#include "../drawing/line.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test 0: draw line");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        Line(sf::Vector2f(20 + clock() * 10.0 / CLOCKS_PER_SEC, 30), sf::Vector2f(145, 5)).draw(window);
        window.display();
    }

    return 0;
}