#include "ball-queue.h"
#include <cmath>
#include <memory>
#include <math.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>

constexpr float kLauncherLength = 125;
constexpr float kLauncherWidth = 75;
constexpr float kLauncherBorder = 2;

constexpr float kIndicatorLength = 130;
constexpr float kIndicatorWidth = 35;
constexpr float kIndicatorBorder = 5;

BallQueue::BallQueue() {
    background = std::make_unique<sf::RectangleShape>(sf::Vector2f(kLauncherLength,kLauncherWidth));
    background->setOrigin(sf::Vector2f(kLauncherLength / 2,kLauncherWidth / 2));
    background->setPosition(sf::Vector2f(kLauncherLength / 2,kLauncherWidth / 2));
    background->setRotation(-45);
    background->setOutlineThickness(kLauncherBorder);
    background->setOutlineColor(sf::Color(161, 161, 161));
    background->setFillColor(sf::Color(100, 105, 112));

    indicator = std::make_unique<sf::RectangleShape>(sf::Vector2f(kIndicatorLength, kIndicatorWidth));
    indicator->setPosition(sf::Vector2f(0, kLauncherWidth));
    indicator->setOutlineThickness(kIndicatorBorder);
    indicator->setOutlineColor(sf::Color(48, 48, 48));
    indicator->setFillColor(sf::Color(69, 69, 69));
}

void BallQueue::add(Ball& ball) {
    balls.push(std::make_unique<Ball>(ball));
    indicator->setFillColor(balls.front()->getFillColor());
}

Ball BallQueue::dispense() {
    constexpr float kLaunchVelocity = 3;
    const float x_velocity = abs(kLaunchVelocity * cos(background->getRotation()));
    const float y_velocity = -abs(kLaunchVelocity * sin(background->getRotation()));

    Ball dispensed = *balls.front();
    balls.pop();

    dispensed.setPosition(getPosition() + sf::Vector2f(kIndicatorLength / 2, kLauncherWidth / 3));
    dispensed.setVelocity(sf::Vector2f(x_velocity, y_velocity));

    if (!balls.empty()) {
        indicator->setFillColor(balls.front()->getFillColor());
    } else {
        indicator->setFillColor(sf::Color(69, 69, 69));
    }

    return dispensed;
}

void BallQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(*background, getTransform());
    target.draw(*indicator, getTransform());
}
