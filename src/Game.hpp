#pragma once
#include <SFML/Graphics.hpp>
#include "LevelData.hpp"
#include <memory>
#include <vector>

class State;   //dichiarazione condivisa per il compile time

class Game{
    sf::RenderWindow window;
    sf::Texture textureBg;
    sf::Sprite background;
    std::unique_ptr<State> currentState;
    std::vector<LevelData> levelContainers;
    public:
        Game(unsigned width, unsigned height, const std::string& title);
        ~Game();
        void changeState(std::unique_ptr<State> newState);
        void run();
        void requestClose();
        LevelData getLvlSetup(unsigned lvl);
};

