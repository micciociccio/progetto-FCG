#include "LevelsState.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "GameUtils.hpp"

LevelsState::LevelsState(Game& g)
:   game(g),
    userLevel(game.getUserLvl()),
    descMsg(game.getGenFont(), "Enter a level\n to play", 47),
    lvlBox(game.getGenFont(), "", 50),
    warnMsg(game.getGenFont(), "Maximum level\n you can choose: "+std::to_string(userLevel), 40),
    rect({140.0f, 70.0f})
    {
        descMsg.setOutlineThickness(0.4f); lvlBox.setOutlineThickness(0.4f); warnMsg.setOutlineThickness(0.4f);
        descMsg.setOutlineColor(sf::Color::Black); lvlBox.setOutlineColor(sf::Color::Black); warnMsg.setOutlineColor(sf::Color::Black);
        warnMsg.setLineAlignment(sf::Text::LineAlignment::Center); descMsg.setLineAlignment(sf::Text::LineAlignment::Center);
        utils::centerOrigin(descMsg); utils::centerOrigin(lvlBox); utils::centerOrigin(warnMsg);
        sf::FloatRect rectBounds=rect.getLocalBounds();
        rect.setOrigin({
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
        if((unicode>'0' && unicode<='9' && input.size()<2) || (unicode=='0' && input.size()>0)){   //qua accettiamo i livelli da 1 a 10
            input+=static_cast<char>(unicode);
            if(std::stoi(input)>10){
                input="10";
            }
            lvlBox.setString(input);
            lvlBox.setLineAlignment(sf::Text::LineAlignment::Center);
            utils::centerOrigin(lvlBox);
        }
    }
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(input.size()>0  && std::stoi(input)<=userLevel){
                game.changeState(std::make_unique<PlayingState>(game, std::stoi(input), 0));
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