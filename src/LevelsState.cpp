#include "LevelsState.hpp"
#include "PlayingState.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "GameUtils.hpp"

LevelsState::LevelsState(Game& g, unsigned capLevel)
:   game(g),
    capLvl(capLevel),
    font("assets/JetBrainsMonoNL-LightItalic.ttf"),
    desc(font, "Inserisci un livello da giocare", 20),
    lvlBox(font, "", 30),
    rect({140.0f, 80.0f}){
        utils::centerOrigin(desc); utils::centerOrigin(lvlBox);
        sf::FloatRect rectBounds=rect.getLocalBounds();
        rect.setOrigin({
            rectBounds.position.x+rectBounds.size.x/2.0f,
            rectBounds.position.y+rectBounds.size.y/2.0f
        });
        rect.setPosition({utils::width/2.0f, utils::height/2.0f-100.0f});
        desc.setPosition({rect.getPosition().x, rect.getPosition().y-140.0f});
        lvlBox.setPosition({rect.getPosition().x, rect.getPosition().y});
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2.0f);     
}

LevelsState::~LevelsState()=default;

void LevelsState::handleEvent(const sf::Event& event){
    if(const auto* textEntered=event.getIf<sf::Event::TextEntered>()){
        char32_t unicode=textEntered->unicode;
        if(unicode>'0' && unicode<'9' && input.size()<2){
            input+=static_cast<char>(unicode);
            lvlBox.setString(input);
            lvlBox.setLineAlignment(sf::Text::LineAlignment::Center);
            utils::centerOrigin(lvlBox);
        }
    }
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(std::stoi(input)<=capLvl){
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
            game.changeState(std::make_unique<MenuState>(game, capLvl));
        }
    }
}

void LevelsState::update(float dt){

}

void LevelsState::render(sf::RenderWindow& window){
    window.draw(desc); window.draw(rect); window.draw(lvlBox);
}