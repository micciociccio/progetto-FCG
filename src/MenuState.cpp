#include "MenuState.hpp"
#include "State.hpp"
#include "Game.hpp"

MenuState::MenuState(Game& g)
:   game(g),
    font("DejavuSansMono-5m7L.ttf"),
    title(font, "aa", 70),
    selectedIndex(0){
        centerOrigin(title);
        title.setPosition({240.0f, 80.0f});
        std::vector<std::string> labels={"levels", "play", "exit"};
        float fixedX=240.0f, startY=340.0f;
        for(int i=0; i<labels.size(); i++){
            sf::Text option(font, labels[i], 15);
            centerOrigin(option);
            option.setPosition({fixedX, startY + static_cast<float>(i) * 60.0f});
            options.push_back(option);
        }
}   

void MenuState::centerOrigin(sf::Text& t){
    sf::FloatRect bounds=t.getLocalBounds();
    t.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
}

MenuState::~MenuState()=default;

void MenuState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0) selectedIndex--;
        }
        if(keyPressed->code==sf::Keyboard::Key::Down){
            if(selectedIndex<2) selectedIndex++;
        }
        if(keyPressed->code==sf::Keyboard::Key::Enter){
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