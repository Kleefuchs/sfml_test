#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "Boykissies");
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
}
