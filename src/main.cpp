#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <vector>
#include "foreign/SimpleSpriteBatcher.hpp"

#define WIDTH 1920
#define HEIGHT 1080

#define NUMBER_OF_BOYKISSERS 100000

void draw(sf::RenderWindow* window, sf::Sprite* background, sf::Sprite* player,
          std::vector<sf::Sprite>* boykissers,
          SimpleSpriteBatcher* boykisserBatcher,
          std::vector<std::optional<sf::Sprite>>* kissHearts,
          SimpleSpriteBatcher* kissHeartsBatcher) {
    window->clear();
    window->draw(*background);
    boykisserBatcher->batchSprites(*boykissers);
    window->draw(*boykisserBatcher);
    window->draw(*player);
    window->draw(*kissHeartsBatcher);
    for (size_t i = 0; i < kissHearts->size(); i++) {
        if (!kissHearts->at(i).has_value()) {
            continue;
        }
        window->draw(*kissHearts->at(i));
    }
}

void update(sf::Clock* deltaTimeClock, sf::Sprite* player, sf::Clock* kissTimer,
            sf::Texture* kissHeartTexture,
            std::vector<std::optional<sf::Sprite>>* kissHearts,
            std::vector<sf::Sprite>* boykissers) {
    float deltaTime = deltaTimeClock->restart().asSeconds();
    /*This checks for boykissers to kiss and then spawns hearts when the kisstimer reaches a value over 500*/
    for (size_t i = 0; i < boykissers->size(); i++) {
        if (player->getGlobalBounds().findIntersection(
                boykissers->at(i).getGlobalBounds())) {
            if (kissTimer->getElapsedTime().asMilliseconds() > 500) {
                sf::Sprite kissHeart(*kissHeartTexture);
                kissHeart.setPosition(player->getPosition());
                kissHearts->push_back(kissHeart);
            }
        }
    }

    /*Animates every existing kissHeart*/
    for (size_t i = 0; i < kissHearts->size(); i++) {
        if (!kissHearts->at(i).has_value()) {
            continue;
        }
        if (kissHearts->at(i).value().getPosition().y -
                player->getPosition().y <
            -250) {
            kissHearts->at(i) = std::nullopt;
        } else {
            kissHearts->at(i).value().move(
                {(float)(rand() % 400 - 200) * deltaTime, -50.0f * deltaTime});
        }
    }

    if (kissTimer->getElapsedTime().asMilliseconds() > 500) {
        kissTimer->restart();
    }

    if (kissHearts->size() > 100000) {
        kissHearts->clear();
    }

    // Stoopid ass movement code
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        player->move({-200.f * deltaTime, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        player->move({200.f * deltaTime, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        player->move({0.0f, 200.f * deltaTime});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        player->move({0.0f, -200.f * deltaTime});
}

int main() {
    sf::Clock kissTimer;
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}),
                            "Boykisser Game UwU :3");
    // window.setFramerateLimit(180);

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

    /*Spawns boykissers at random locations*/
    for (int i = 0; i < NUMBER_OF_BOYKISSERS; i++) {
        sf::Sprite boykisser(boykisserTexture);
        boykisser.setPosition(
            {(float)(std::rand() % (WIDTH - boykisserTexture.getSize().x)), (float)(std::rand() % (HEIGHT - boykisserTexture.getSize().y))});
        boykissers.push_back(boykisser);
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        update(&deltaTimeClock, &player, &kissTimer, &kissHeartTexture,
               &kissHearts, &boykissers);

        draw(&window, &background, &player, &boykissers, &boykisserBatcher,
             &kissHearts, &kissHeartsBatcher);
        window.display();
    }
}
