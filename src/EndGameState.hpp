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
    std::size_t level, selectedIndex, attempts;
    public:
        explicit EndGameState(Game& g, bool go, std::size_t lvl, std::size_t attempts);
        ~EndGameState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};