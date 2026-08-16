#include "MenuState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"
#include "GameUtils.hpp"
#include "LevelsState.hpp"

MenuState::MenuState(Game& g)
:   game(g),
    title(game.getTitleFont(), "aa", 200),
    selectedIndex(0),
    userLevel(game.getUserLvl()){
        utils::centerOrigin(title);
        title.setPosition({utils::width/2.0f, 170.0f});
        std::vector<std::string> labels={"Levels", "Play", "Exit"};
        for(std::size_t i=0; i<labels.size(); i++){
            sf::Text option(game.getGenFont(), labels[i], 40);
            option.setOutlineThickness(0.4f);
            option.setOutlineColor(sf::Color::Black);
            utils::centerOrigin(option);
            option.setPosition({utils::width/2.0f, 450.0f + static_cast<float>(i) * 90.0f});
            options.push_back(option);
        }
        title.setOutlineThickness(1.3f);
        title.setOutlineColor(sf::Color::Black);
        utils::updateColors(options, selectedIndex);
}   

MenuState::~MenuState()=default;

void MenuState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0){
                selectedIndex--;
                game.playSound(SoundEffect::MenuSelect);
                utils::updateColors(options, selectedIndex);
            } 
        }
        else if(keyPressed->code==sf::Keyboard::Key::Down){
            if(static_cast<std::size_t>(selectedIndex) < options.size()-1){
                selectedIndex++;
                game.playSound(SoundEffect::MenuSelect);
                utils::updateColors(options, selectedIndex);
            } 
        }
        else if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(selectedIndex==0){   //levels premuto
                game.changeState(std::make_unique<LevelsState>(game));
            }
            else if(selectedIndex==1){   //play premuto, user continua dall'ultimo livello
                game.changeState(std::make_unique<PlayingState>(game, userLevel, 0));
            }
            else{   //exit premuto, ci occupiamo solo di chiudere la window
                game.requestClose();
            }                
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



