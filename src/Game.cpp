#include "Game.hpp"
#include "State.hpp"
#include "MenuState.hpp"

Game::Game(unsigned width, unsigned height, const std::string& title)
	: window(sf::VideoMode({width, height}), title, sf::Style::Titlebar){
		currentState=std::make_unique<MenuState>(*this);
}

Game::~Game()=default;

void Game::changeState(std::unique_ptr<State> newState){
	currentState=std::move(newState);
}

void Game::run(){
	sf::Clock clock;
	while(window.isOpen()){
    	while(const std::optional event=window.pollEvent()){
            currentState->handleEvent(*event);   //dispatch dinamico allo stato attivo, con * deferenzio l'optional dell'evento 
        }
        float dt=std::min(clock.restart().asSeconds(), 0.05f);
        currentState->update(dt);
        window.clear();
        currentState->render(window);
        window.display();
    }
}

void Game::requestClose(){
	window.close();
}