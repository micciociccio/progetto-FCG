#include "LevelsState.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "GameUtils.hpp"

LevelsState::LevelsState(Game& g)
:   game(g),
    userLevel(game.getUserLvl()),
    descMsg(game.getFont(Fonts::Gen), "Enter a level\n to play", 47),
    lvlBox(game.getFont(Fonts::Gen), "", 50),
    warnMsg(game.getFont(Fonts::Gen), "Maximum level\n you can choose: "+std::to_string(userLevel), 40),
    rect({140.0f, 70.0f})
    {
        utils::makeBorder(descMsg, 0.4f, sf::Color::Black);
        utils::makeBorder(lvlBox, 0.4f, sf::Color::Black);
        utils::makeBorder(warnMsg, 0.4f, sf::Color::Black);
        warnMsg.setLineAlignment(sf::Text::LineAlignment::Center); descMsg.setLineAlignment(sf::Text::LineAlignment::Center);
        utils::centerOrigin(descMsg); utils::centerOrigin(lvlBox); utils::centerOrigin(warnMsg);
        sf::FloatRect rectBounds=rect.getLocalBounds();
        rect.setOrigin({   //mettiamo pos al centro del rettangolo
            rectBounds.position.x+rectBounds.size.x/2.0f,
            rectBounds.position.y+rectBounds.size.y/2.0f
        }); 
        rect.setPosition({utils::width/2.0f, utils::height/2.0f-60.0f});
        descMsg.setPosition({rect.getPosition().x, rect.getPosition().y-170.0f});
        lvlBox.setPosition({rect.getPosition().x, rect.getPosition().y});
        warnMsg.setPosition({rect.getPosition().x, rect.getPosition().y+200.0f});
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2.0f);   
}

LevelsState::~LevelsState()=default;

void LevelsState::handleEvent(const sf::Event& event){
    if(const auto* textEntered=event.getIf<sf::Event::TextEntered>()){
        char32_t unicode=textEntered->unicode;
        if(input.size()<2){   //qua accettiamo i livelli da 1 a 10
            if((unicode>'0' && unicode<='9')  || (unicode=='0' && input.size()>0)){   
                input+=static_cast<char>(unicode);
                if(static_cast<unsigned>(std::stoul(input))>utils::lastLvl) input="10";
                lvlBox.setString(input);
                lvlBox.setLineAlignment(sf::Text::LineAlignment::Center);
                utils::centerOrigin(lvlBox);
            }
        }
    }
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(input.size()>0){
                unsigned level=static_cast<unsigned>(std::stoul(input));   //stoul string to unsigned
                if(level<=userLevel) game.changeState(std::make_unique<PlayingState>(game, level, 0));   
            }
        }
        else if(keyPressed->code==sf::Keyboard::Key::Backspace){
            if(!input.empty()){
                input.pop_back();
                lvlBox.setString(input);
                lvlBox.setLineAlignment(sf::Text::LineAlignment::Center);
                utils::centerOrigin(lvlBox);
            }
        }
        else if(keyPressed->code==sf::Keyboard::Key::Escape){
            game.changeState(std::make_unique<MenuState>(game));
        }
    }
}

void LevelsState::update(float dt){

}

void LevelsState::render(sf::RenderWindow& window){
    window.draw(descMsg); window.draw(warnMsg);
    window.draw(rect); window.draw(lvlBox); 
}