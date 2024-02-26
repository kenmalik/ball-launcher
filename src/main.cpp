#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include "ball-queue.h"

constexpr float SCREEN_WIDTH = 1400;
constexpr float SCREEN_HEIGHT = 1000;

void UpdatePositions(std::vector<Ball>&, sf::Time&);

int main() {
    constexpr float STARTING_VELOCITY_X = 1;
    constexpr float STARTING_VELOCITY_Y = -3;

    std::vector<Ball> active_balls;
    active_balls.push_back(Ball(15, sf::Vector2f(STARTING_VELOCITY_X, STARTING_VELOCITY_Y)));
    active_balls.at(0).setPosition(0, SCREEN_HEIGHT - (2.5 * active_balls.at(0).getRadius()));

    BallQueue ball_queue;

    Ball selector_ball(10, sf::Vector2f(0,0));
    selector_ball.setFillColor(sf::Color::Green);

    sf::Clock clock;
    sf::Time timer = sf::milliseconds(0);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window");
    while (window.isOpen()) {
        timer += clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.key.code == sf::Keyboard::Left) {
                selector_ball.setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Right) {
                selector_ball.setFillColor(sf::Color::Green);
            }
            if (event.key.code == sf::Keyboard::Space) {
                active_balls.push_back(ball_queue.dispense());
            }
            if (event.key.code == sf::Keyboard::R) {
                ball_queue.add(selector_ball);
            }
        }

        window.clear();
        for (int i = 0; i < active_balls.size(); ++i) {
            window.draw(active_balls.at(i));
            UpdatePositions(active_balls, timer);
        }

        selector_ball.move(selector_ball.getVelocity());

        window.draw(ball_queue);
        window.draw(selector_ball);
        window.display();
    }
    return 0;
}

void UpdatePositions(std::vector<Ball>& active_balls, sf::Time& timer) {
        for (int i = 0; i < active_balls.size(); ++i) {
            active_balls.at(i).move(active_balls.at(i).velocity);
            if (timer >= sf::milliseconds(100)) {
                active_balls.at(i).velocity.y += .005;
            }

            if (active_balls.at(i).getPosition().y >= SCREEN_HEIGHT - active_balls.at(i).getRadius() * 2) {
                active_balls.erase(active_balls.begin() + i);
            }
        }


}
