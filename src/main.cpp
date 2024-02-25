#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "ball.h"

int main() {
    constexpr float SCREEN_WIDTH = 1800;
    constexpr float SCREEN_HEIGHT = 1600;

    std::vector<Ball> balls;
    balls.push_back(Ball(15, sf::Vector2f(0,.1)));

    Ball ball(10, sf::Vector2f(0,0));
    ball.setFillColor(sf::Color::Green);

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
                ball.setFillColor(sf::Color::Red);
            }
            if (event.key.code == sf::Keyboard::Right) {
                ball.setFillColor(sf::Color::Green);
            }
        }

        window.clear();

        ball.move(ball.getVelocity());

        for (int i = 0; i < balls.size(); ++i) {
            balls.at(i).move(balls.at(i).velocity);
            if (timer >= sf::milliseconds(1000)) {
                balls.at(i).velocity.y += .005;
            }
            window.draw(balls.at(i));

            if (balls.at(i).getPosition().y >= SCREEN_HEIGHT / 2) {
                balls.erase(balls.begin() + i);
            }
        }

        window.draw(ball);
        window.display();
    }
    return 0;
}
