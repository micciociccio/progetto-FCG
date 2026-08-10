#include "Game.hpp"
#include "State.hpp"
#include "MenuState.hpp"
#include "GraphicsUtils.hpp"

Game::Game(unsigned width, unsigned height, const std::string& title)
:   window(sf::VideoMode({width, height}), title, sf::Style::Titlebar),
    textureBg("assets/background.jpg"),
    background(textureBg){
        textureBg.setSmooth(true);
        window.setVerticalSyncEnabled(true);
        sf::Vector2u textureSize=textureBg.getSize();
        float scale=std::max(   //cover approach, riempiamo tutta la window senza deformare l'immagine
            utils::width/static_cast<float>(textureSize.x),
            utils::height/static_cast<float>(textureSize.y)
        );
        background.setScale({scale, scale});
		currentState=std::make_unique<MenuState>(*this);
}

Game::~Game()=default;

void Game::changeState(std::unique_ptr<State> newState){
	currentState=std::move(newState);
}

void Game::run(){
	sf::Clock clock;
	while(window.isOpen()){
    	while(const std::optional<sf::Event> event=window.pollEvent()){
            currentState->handleEvent(*event);   //dispatch dinamico allo stato attivo, con * deferenzio l'optional dell'evento 
        }
        float dt=std::min(clock.restart().asSeconds(), 0.05f);
        currentState->update(dt);
        window.clear();
        window.draw(background);
        currentState->render(window);
        window.display();
    }
}

void Game::requestClose(){
	window.close();
}