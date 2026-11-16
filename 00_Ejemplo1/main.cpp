#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({600, 400}),
        "Imagen SFML"
    );

    sf::Texture texture("Leon.jpg");
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}