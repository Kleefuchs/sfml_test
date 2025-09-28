#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({1600, 900}),
                            "Boykisser Game UwU :3");
    const sf::Texture playerTexture("assets/player.png");
    sf::Sprite player(playerTexture);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(player);
        window.display();
    }
}
