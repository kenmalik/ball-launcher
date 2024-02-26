#ifndef BALL_QUEUE_H
#define BALL_QUEUE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <queue>
#include <vector>

#include "ball.h"

class BallQueue : public sf::Drawable {
    public:
        BallQueue();

        sf::Vector2f getPosition();

        void add(Ball&);
        Ball dispense();

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    private:
        sf::Vector2f position;
        std::queue<std::unique_ptr<Ball>> balls;
        std::unique_ptr<sf::RectangleShape> background;
        std::vector<std::unique_ptr<sf::RectangleShape>> loaded;
};

#endif
