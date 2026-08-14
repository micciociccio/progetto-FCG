#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <string>
#include <memory>

class Game;

class LevelsState : public State{
    Game& game;
    unsigned capLvl;
    sf::Font font;
    sf::Text desc, lvlBox;
    sf::RectangleShape rect;
    std::string input;
    public:
        explicit LevelsState(Game& g, unsigned capLevel);
        ~LevelsState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};