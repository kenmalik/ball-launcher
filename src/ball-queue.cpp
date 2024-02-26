#include "ball-queue.h"
#include <cmath>
#include <memory>

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
    launcher = std::make_unique<sf::RectangleShape>(sf::Vector2f(kLauncherLength,kLauncherWidth));
    launcher->setOrigin(sf::Vector2f(kLauncherLength / 2,kLauncherWidth / 2));
    launcher->setPosition(sf::Vector2f(kLauncherLength / 2,kLauncherWidth / 2));
    launcher->setRotation(-45);
    launcher->setOutlineThickness(kLauncherBorder);
    launcher->setOutlineColor(sf::Color(161, 161, 161));
    launcher->setFillColor(sf::Color(100, 105, 112));

    indicator = std::make_unique<sf::RectangleShape>(sf::Vector2f(kIndicatorLength, kIndicatorWidth));
    indicator->setPosition(sf::Vector2f(0, kLauncherWidth));
    indicator->setOutlineThickness(kIndicatorBorder);
    indicator->setOutlineColor(sf::Color(48, 48, 48));
    indicator->setFillColor(sf::Color(69, 69, 69));
}

sf::RectangleShape& BallQueue::get_launcher() { return *launcher; }

bool BallQueue::empty() { return balls.empty(); }

void BallQueue::add(Ball& ball) {
    balls.push(std::make_unique<Ball>(ball));
    indicator->setFillColor(balls.front()->getFillColor());
}

void BallQueue::rotateLeft() {
    launcher->rotate(-1);
}

void BallQueue::rotateRight() {
    launcher->rotate(1);
}

Ball BallQueue::dispense() {
    constexpr float kLaunchVelocity = 3;
    const float x_velocity = kLaunchVelocity * std::cos(launcher->getRotation() * (M_PI / 180));
    const float y_velocity = kLaunchVelocity * std::sin(launcher->getRotation() * (M_PI / 180));

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

    target.draw(*launcher, getTransform());
    target.draw(*indicator, getTransform());
}
