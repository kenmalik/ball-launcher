#ifndef BALL_QUEUE_H
#define BALL_QUEUE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <queue>

#include "ball.h"

class BallQueue : public sf::Drawable, public sf::Transformable {
    public:
        BallQueue();
        void add(Ball&);
        Ball dispense();
        sf::RectangleShape& get_launcher();
        bool empty();
        void rotateLeft();
        void rotateRight();
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    private:
        sf::Vector2f position;
        std::queue<std::unique_ptr<Ball>> balls;
        std::unique_ptr<sf::RectangleShape> launcher;
        std::unique_ptr<sf::RectangleShape> indicator;
};

#endif
