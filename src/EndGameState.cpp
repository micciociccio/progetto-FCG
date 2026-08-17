#include "EndGameState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "GameUtils.hpp"
#include <string>

EndGameState::EndGameState(Game& g, bool go, unsigned lvl, unsigned fails)
:   game(g),
    gameover(go),
    level(lvl),
    failures(fails),
    selectedIndex(0),
    title(game.getFont(Fonts::Title)),
    textAttempts(game.getFont(Fonts::Title), "", 50),
    textLevel(game.getFont(Fonts::Title), "level "+std::to_string(level), 50){
        title.setCharacterSize(120);
        utils::makeBorder(title, 0.4f, sf::Color::Black);
        utils::makeBorder(textAttempts, 0.4f, sf::Color::Black);
        utils::makeBorder(textLevel, 0.4f, sf::Color::Black);
        std::vector<std::string> labels;
        std::string s=(failures==0) ? "with "+std::to_string(failures+1) + " attempt" : "with "+std::to_string(failures+1) + " attempts";
        textAttempts.setString(s);
        utils::centerOrigin(textAttempts); utils::centerOrigin(textLevel);
        if(gameover){
            title.setString("Failed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            textLevel.setPosition({title.getPosition().x, title.getPosition().y+130.0f});
            labels={"Play again", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(game.getFont(Fonts::Gen), labels[i], 40);
                utils::makeBorder(option, 0.4f, sf::Color::Black);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 500.0f + static_cast<float>(i) * 90.0f});
                options.push_back(option);
            }
        }
        else{
            //controllo per update userLvl se il livello superato era il resume dell'user, altrimenti non facciamo nulla è stato passato un livello vecchio
            if(level>=game.getUserLvl()){
                if(level==utils::lastLvl) game.updateUserLvl(utils::lastLvl);
                else game.updateUserLvl(level+1);
            }
            title.setString("Passed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            textAttempts.setPosition({title.getPosition().x, title.getPosition().y+130.0f});
            labels={"Next level", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(game.getFont(Fonts::Gen), labels[i], 40);
                utils::makeBorder(option, 0.4f, sf::Color::Black);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 500.0f + static_cast<float>(i) * 90.0f});
                options.push_back(option);
            }
        }
        utils::updateColors(options, selectedIndex);
    }

EndGameState::~EndGameState()=default;


void EndGameState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Down){
            if(selectedIndex < options.size()-1){
                selectedIndex++;
                game.playSound(SoundEffect::MenuSelect);
                utils::updateColors(options, selectedIndex);
            } 
        }
        else if(keyPressed->code==sf::Keyboard::Key::Up){
            if(selectedIndex>0){
                selectedIndex--;
                game.playSound(SoundEffect::MenuSelect);
                utils::updateColors(options, selectedIndex);
            }
        }
        else if(keyPressed->code==sf::Keyboard::Key::Enter){
            if(selectedIndex==0){
                if(gameover){   //play again si richiama sullo stesso livello
                    game.changeState(std::make_unique<PlayingState>(game, level, ++failures));
                }
                else{   //si avanza di livello, ++level e azzeriamo i fallimenti
                    if(level==utils::lastLvl) game.changeState(std::make_unique<PlayingState>(game, utils::lastLvl, 0));   //evitiamo di fare display di lastLvl+1
                    else game.changeState(std::make_unique<PlayingState>(game, ++level, 0));
                }
            }
            else if(selectedIndex==1){
                game.requestClose();
            }
        }
        else if(keyPressed->code==sf::Keyboard::Key::Escape){
            game.changeState(std::make_unique<MenuState>(game)); 
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
    if(gameover) window.draw(textLevel); 
    else window.draw(textAttempts);
}





