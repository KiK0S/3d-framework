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
        Line(100, 20).draw(window);
        window.display();
    }

    return 0;
}