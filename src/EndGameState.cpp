#include "EndGameState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "GameUtils.hpp"
#include "LevelLoader.hpp"

EndGameState::EndGameState(Game& g, bool go, unsigned lvl, unsigned fails)
:   game(g),
    gameover(go),
    level(lvl),
    selectedIndex(0),
    failures(fails),
    title(game.getTitleFont()),
    textAttempts(game.getTitleFont(), "", 50),
    textLevel(game.getTitleFont(), "level "+std::to_string(level), 50){
        title.setCharacterSize(120);
        title.setOutlineThickness(0.4f); textAttempts.setOutlineThickness(0.4f); textLevel.setOutlineThickness(0.4f);
        title.setOutlineColor(sf::Color::Black); textAttempts.setOutlineColor(sf::Color::Black); textLevel.setOutlineColor(sf::Color::Black);
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
                sf::Text option(game.getGenFont(), labels[i], 40);
                option.setOutlineThickness(0.4f); option.setOutlineColor(sf::Color::Black);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 500.0f + static_cast<float>(i) * 90.0f});
                options.push_back(option);
            }
        }
        else{
            //controllo per update userLvl se il livello superato era il resume dell'user
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
                sf::Text option(game.getGenFont(), labels[i], 40);
                option.setOutlineThickness(0.4f); option.setOutlineColor(sf::Color::Black);
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
            if(static_cast<std::size_t>(selectedIndex) < options.size()-1){
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
    else{
        window.draw(textAttempts);
    }
}





