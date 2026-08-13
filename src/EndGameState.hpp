#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <string>

class Game;

class EndGameState : public State{
    Game& game;
    bool gameover;
    sf::Font fontTit, fontOpt;
    std::size_t level, selectedIndex, failures;
    sf::Text title, textAttempts, textLevel;
    std::vector<sf::Text> options;
    public:
        explicit EndGameState(Game& g, bool go, std::size_t lvl, std::size_t fails);
        ~EndGameState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};