#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <vector>
#include "foreign/SimpleSpriteBatcher.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}),
                            "Boykisser Game UwU :3");
    SimpleSpriteBatcher ssBatcher;
    std::srand(std::time({}));
    sf::Clock deltaTimeClock;
    sf::Texture playerTexture("../assets/player.png");
    sf::Sprite player(playerTexture);

    sf::Texture boykisserTexture("../assets/boykisser.png");
    boykisserTexture.setSmooth(false);
    ssBatcher.texture = &boykisserTexture;
    std::vector<sf::Sprite> boykissers;

    for (int i = 0; i < 10; i++) {
        sf::Sprite boykisser(boykisserTexture);
        boykisser.setPosition(
            {(float)(std::rand() % 1800), (float)(std::rand() % 900)});
        boykissers.push_back(boykisser);
    }

    while (window.isOpen()) {
        float deltaTime = deltaTimeClock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            player.move({-200.f * deltaTime, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            player.move({200.f * deltaTime, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            player.move({0.0f, 200.f * deltaTime});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            player.move({0.0f, -200.f * deltaTime});

        window.clear();
        ssBatcher.batchSprites(boykissers);
        window.draw(ssBatcher);
        window.draw(player);
        window.display();
    }
}
