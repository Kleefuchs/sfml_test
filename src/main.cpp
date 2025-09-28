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
    sf::Clock kissTimer;
    sf::RenderWindow window(sf::VideoMode({1920, 1080}),
                            "Boykisser Game UwU :3");
    window.setFramerateLimit(180);

    sf::Texture backgroundTexture("../assets/background");
    sf::Sprite background(backgroundTexture);

    sf::Texture kissHeartTexture("../assets/kiss_heart");
    kissHeartTexture.setSmooth(true);
    std::vector<std::optional<sf::Sprite>> kissHearts;
    SimpleSpriteBatcher kissHeartsBatcher;
    kissHeartsBatcher.texture = &kissHeartTexture;

    std::srand(std::time({}));
    sf::Clock deltaTimeClock;
    sf::Texture playerTexture("../assets/player");
    playerTexture.setSmooth(true);
    sf::Sprite player(playerTexture);

    sf::Texture boykisserTexture("../assets/boykisser");
    boykisserTexture.setSmooth(true);
    SimpleSpriteBatcher boykisserBatcher;
    boykisserBatcher.texture = &boykisserTexture;
    std::vector<sf::Sprite> boykissers;

    for (int i = 0; i < 50; i++) {
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

        for (size_t i = 0; i < boykissers.size(); i++) {
            if (player.getGlobalBounds().findIntersection(
                    boykissers[i].getGlobalBounds())) {
                if (kissTimer.getElapsedTime().asMilliseconds() > 500) {
                    sf::Sprite kissHeart(kissHeartTexture);
                    kissHeart.setPosition(player.getPosition());
                    kissHearts.push_back(kissHeart);
                }
            }
        }

        if (kissTimer.getElapsedTime().asMilliseconds() > 500) {
            kissTimer.restart();
        }

        for (size_t i = 0; i < kissHearts.size(); i++) {
            if (!kissHearts[i].has_value()) {
                continue;
            }
            if (kissHearts[i]->getPosition().y - player.getPosition().y < -250) {
                kissHearts[i] = std::nullopt;
            } else {
                kissHearts[i]->move({(float) (rand() % 400 - 200) * deltaTime, -50.0f * deltaTime});
            }
        }

        if (kissHearts.size() > 100000) {
            kissHearts.clear();
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
        window.draw(background);
        boykisserBatcher.batchSprites(boykissers);
        window.draw(boykisserBatcher);
        window.draw(player);
        window.draw(kissHeartsBatcher);
        for (size_t i = 0; i < kissHearts.size(); i++) {
            if (!kissHearts[i].has_value()) {
                continue;
            }
            window.draw(*kissHearts[i]);
        }
        window.display();
    }
}
