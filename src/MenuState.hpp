#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <vector>

class Game;

class MenuState : public State{   //estensione di State
    Game& game;
    sf::Text title;
    std::vector<sf::Text> options;
    std::size_t selectedIndex;
    unsigned userLevel;
    public:
        explicit MenuState(Game& g);
        ~MenuState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};
