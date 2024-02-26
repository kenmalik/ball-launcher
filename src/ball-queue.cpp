#include "ball-queue.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

BallQueue::BallQueue() {
    background = std::make_unique<sf::RectangleShape>(sf::Vector2f(100,100));
    background->setFillColor(sf::Color::Green);
}

sf::Vector2f BallQueue::getPosition() { return position; };

void BallQueue::add(Ball& ball) {
    balls.push(std::make_unique<Ball>(ball));
    loaded.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(150,150)));
}

Ball BallQueue::dispense() {
    Ball dispensed = *balls.front();
    balls.pop();
    loaded.pop_back();
    return dispensed;
}

void BallQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*background);
    
    for (auto const& rect : loaded) {
        target.draw(*rect);
    }
}
