#include "MenuState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "GraphicsUtils.hpp"

MenuState::MenuState(Game& g)
:   game(g),
    font("DejavuSansMono-5m7L.ttf"),
    title(font, "aa", 110),
    selectedIndex(0){
        utils::centerOrigin(title);
        title.setPosition({240.0f, 100.0f});
        std::vector<std::string> labels={"levels", "play", "exit"};
        for(std::size_t i=0; i<labels.size(); i++){
            sf::Text option(font, labels[i], 21);
            utils::centerOrigin(option);
            option.setPosition({utils::width/2.0f, 360.0f + static_cast<float>(i) * 60.0f});
            options.push_back(option);
        }
        updateColors();
}   

MenuState::~MenuState()=default;

void MenuState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0) selectedIndex--;
            updateColors();
        }
        else if(keyPressed->code==sf::Keyboard::Key::Down){
            if(selectedIndex<options.size()-1) selectedIndex++;
            updateColors();
        }
        else if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(selectedIndex==0){}
            else if(selectedIndex==1){
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

void MenuState::updateColors(){
    for(std::size_t i=0; i<options.size(); i++){
        if(i==selectedIndex){
            options[i].setFillColor(sf::Color::Red);
        }
        else options[i].setFillColor(sf::Color::White);
    }
}

