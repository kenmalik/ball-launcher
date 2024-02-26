#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

class Ball : public sf::CircleShape {
    public:
        Ball(const std::string);
        Ball(float, sf::Vector2f);

        std::string getName();
        sf::Vector2f getVelocity();
        void setVelocity(sf::Vector2f);
        
        sf::Vector2f velocity;
    private:
        std::string name;
};

#endif
