#include "Game.hpp"
#include "State.hpp"
#include "MenuState.hpp"
#include "GraphicsUtils.hpp"
#include "LevelLoader.hpp"

Game::Game(unsigned width, unsigned height, const std::string& title)
:   window(sf::VideoMode({width, height}), title, sf::Style::Titlebar),
    textureBg("assets/background.jpg"),
    background(textureBg),
    levelContainers(loadAllLvl("assets/levels.txt")){
        textureBg.setSmooth(true);
        window.setVerticalSyncEnabled(true);
        sf::Vector2u textureSize=textureBg.getSize();
        float scale=std::max(   //cover approach, riempiamo tutta la window senza deformare l'immagine
            utils::width/static_cast<float>(textureSize.x),
            utils::height/static_cast<float>(textureSize.y)
        );
        background.setScale({scale, scale});
        std::vector<std::string> files={"assets/dotShot.wav", "assets/lvlPassed.mp3", "assets/lvlFailed.wav"};
        //doppio loop obbligatorio perchè in caso di resize il vector modifica i propri indirizzi che poi saranno inaccessibili da sounds[]
        for(std::size_t i=0; i<files.size(); i++){
            sf::SoundBuffer sb(files[i]);
            soundsBuffer.push_back(sb);
        }
        for(std::size_t i=0; i<files.size(); i++){
            sf::Sound sound(soundsBuffer[i]);
            sounds.push_back(sound);
        }
		currentState=std::make_unique<MenuState>(*this);
}

Game::~Game()=default;

void Game::changeState(std::unique_ptr<State> newState){
	currentState=std::move(newState);
}

void Game::run(){
	sf::Clock clock;
	while(window.isOpen()){
        float dt=std::min(clock.restart().asSeconds(), 0.05f);
    	while(const std::optional<sf::Event> event=window.pollEvent()){
            currentState->handleEvent(*event);   //dispatch dinamico allo stato attivo, con * deferenzio l'optional dell'evento 
        }
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

LevelData Game::getLvlSetup(std::size_t lvl){
    unsigned index=std::min(lvl-1, levelContainers.size()-1);
    return levelContainers[index];
}

void Game::playSound(SoundEffect index){
    sounds[static_cast<std::size_t>(index)].play();
}