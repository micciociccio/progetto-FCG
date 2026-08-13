#include "MenuState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"
#include "GraphicsUtils.hpp"

MenuState::MenuState(Game& g)
:   game(g),
    fontTit("assets/DejavuSansMono-5m7L.ttf"),
    fontOpt("assets/JetBrainsMonoNL-LightItalic.ttf"),
    title(fontTit, "aa", 130),
    selectedIndex(0){
        utils::centerOrigin(title);
        title.setPosition({utils::width/2.0f, 150.0f});
        std::vector<std::string> labels={"Levels", "Play", "Exit"};
        for(std::size_t i=0; i<labels.size(); i++){
            sf::Text option(fontOpt, labels[i], 24);
            utils::centerOrigin(option);
            option.setPosition({utils::width/2.0f, 430.0f + static_cast<float>(i) * 80.0f});
            options.push_back(option);
        }
        utils::updateColors(options, selectedIndex);
}   

MenuState::~MenuState()=default;

void MenuState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0) selectedIndex--;
            utils::updateColors(options, selectedIndex);
        }
        else if(keyPressed->code==sf::Keyboard::Key::Down){
            if(selectedIndex < options.size()-1) selectedIndex++;
            utils::updateColors(options, selectedIndex);
        }
        else if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(selectedIndex==0){}
            else if(selectedIndex==1){
                game.changeState(std::make_unique<PlayingState>(game, 1, 0));
            }
            else game.requestClose(); 
        }
    }   
}

void MenuState::update(float dt){
}

void MenuState::render(sf::RenderWindow& window){
    window.draw(title);
    for(sf::Text& option : options){
        window.draw(option);
    }
}



