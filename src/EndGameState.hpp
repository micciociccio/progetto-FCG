#pragma once
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <vector>

class Game;

class EndGameState : public State{
    Game& game;
    bool gameover;
    unsigned level, failures;
    std::size_t selectedIndex;
    sf::Text title, textAttempts, textLevel;
    std::vector<sf::Text> options;
    public:
        explicit EndGameState(Game& g, bool go, unsigned lvl, unsigned fails);
        ~EndGameState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};