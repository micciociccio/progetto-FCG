#include "EndGameState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "GraphicsUtils.hpp"

EndGameState::EndGameState(Game& g, bool go, unsigned lvl)
:   game(g),
    gameover(go),
    fontTit("assets/DejavuSansMono-5m7L.ttf"),
    fontOpt("assets/JetBrainsMonoNL-LightItalic.ttf"),
    title(fontTit),
    selectedIndex(0),
    level(lvl){
        title.setCharacterSize(80);
        std::vector<std::string> labels;
        if(gameover){
            title.setString("Failed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            labels={"Play again", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(fontOpt, labels[i], 24);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 430.0f + static_cast<float>(i) * 80.0f});
                options.push_back(option);
            }
        }
        else{
            title.setString("Passed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            labels={"Next level", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(fontOpt, labels[i], 24);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 430.0f + static_cast<float>(i) * 80.0f});
                options.push_back(option);
            }
        }
        utils::updateColors(options, selectedIndex);
    }

EndGameState::~EndGameState()=default;


void EndGameState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Down){
            if(static_cast<std::size_t>(selectedIndex) < options.size()-1) selectedIndex++;
            utils::updateColors(options, selectedIndex);
        }
        else if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0) selectedIndex--;
            utils::updateColors(options, selectedIndex);
        }
        else if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(selectedIndex==1) game.requestClose();
            else{
                if(gameover){   //play again si richiama sullo stesso livello
                    game.changeState(std::make_unique<PlayingState>(game, level));
                }
                else{   //si avanza di livello, level++
                    game.changeState(std::make_unique<PlayingState>(game, ++level));
                }
            }
        }
    }
}

void EndGameState::update(float dt){
    
}

void EndGameState::render(sf::RenderWindow& window){
    window.draw(title);
    for(sf::Text& option : options){
        window.draw(option);
    }
}





