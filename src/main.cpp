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

    BallQueue ball_queue;
    ball_queue.setPosition(sf::Vector2f(50, SCREEN_HEIGHT * 2/3));

    Ball selector_ball(15, sf::Vector2f(0,0));
    selector_ball.setFillColor(sf::Color::Green);

    constexpr float kMinRotation = 300;
    constexpr float kMaxRotation = 350;
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (ball_queue.get_launcher().getRotation() > kMinRotation) { 
                    ball_queue.rotateLeft();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (ball_queue.get_launcher().getRotation() < kMaxRotation) { 
                    ball_queue.rotateRight();
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::R:
                        selector_ball.setFillColor(sf::Color::Red);
                        break;
                    case sf::Keyboard::G:
                        selector_ball.setFillColor(sf::Color::Green);
                        break;
                    case sf::Keyboard::B:
                        selector_ball.setFillColor(sf::Color::Blue);
                        break;
                    case sf::Keyboard::Space:
                        if (!ball_queue.empty()) {
                            active_balls.push_back(ball_queue.dispense());
                        } else {
                            std::cout << "Queue is empty!" << std::endl;
                        }
                        break;
                    case sf::Keyboard::E:
                        ball_queue.add(selector_ball);
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear();

        UpdatePositions(active_balls, timer);

        for (const Ball& b : active_balls) {
            window.draw(b);
        }
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
