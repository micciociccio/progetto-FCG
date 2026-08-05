#include "Game.hpp"
#include "State.hpp"

Game::Game(unsigned width, unsigned height, const std::string& title)
	: window(sf::VideoMode({width, height}), title){
}

Game::~Game()=default;

void Game::changeState(std::unique_ptr<State> newState){
	currentState=std::move(newState);
}

void Game::run(){
	sf::Clock clock;
    while(window.isOpen()){
        float dt=std::min(clock.restart().asSeconds(), 0.05f);
        window.clear();
        window.display();
    }	
}

void Game::requestClose(){
	window.close();
}