#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class State;   //dichiarazione condivisa per il compile time

class Game{
    sf::RenderWindow window;
    sf::Texture textureBg;
    sf::Sprite background;
    std::unique_ptr<State> currentState;
    public:
        Game(unsigned width, unsigned height, const std::string& title);
        ~Game();
        void changeState(std::unique_ptr<State> newState);
        void run();
        void requestClose();
};

