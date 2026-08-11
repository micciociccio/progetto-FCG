#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"

class Game;

class EndGameState : public State{
    Game& game;
    bool gameover;
    sf::Font fontTit, fontOpt;
    sf::Text title;
    std::vector<sf::Text> options;
    unsigned level, selectedIndex;
    public:
        explicit EndGameState(Game& g, bool go, unsigned lvl);
        ~EndGameState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};