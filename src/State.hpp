#pragma once   //evita di ricompilare la classe astratta più volte per ogni include
#include <SFML/Graphics.hpp>

class State{   //classe astratta pura grazie a metodi virtual e assegnazione pari a 0 
public:
    virtual void handleInput(sf::RenderWindow& window)=0;
    virtual void update(float dt)=0;
    virtual void render(sf::RenderWindow& window)=0;
    virtual ~State()=default;
};