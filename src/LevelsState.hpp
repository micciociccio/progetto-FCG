#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <string>
#include <memory>

class Game;

class LevelsState : public State{
    Game& game;
    unsigned userLevel;
    sf::Font font;
    sf::Text descMsg, lvlBox, warnMsg;
    sf::RectangleShape rect;
    std::string input;
    public:
        explicit LevelsState(Game& g);
        ~LevelsState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};