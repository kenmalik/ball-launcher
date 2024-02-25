#include "ball.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

Ball::Ball(const std::string name) : name(name) {};
Ball::Ball(float sz, sf::Vector2f vel) : sf::CircleShape(sz), velocity(vel) {};

sf::Vector2f Ball::getVelocity() {
    return velocity;
}

void Ball::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}
