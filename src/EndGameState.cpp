#include "EndGameState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "GameUtils.hpp"

EndGameState::EndGameState(Game& g, bool go, std::size_t lvl, std::size_t fails)
:   game(g),
    gameover(go),
    fontTit("assets/DejavuSansMono-5m7L.ttf"),
    fontOpt("assets/JetBrainsMonoNL-LightItalic.ttf"),
    title(fontTit),
    level(lvl),
    selectedIndex(0),
    failures(fails),
    textAttempts(fontTit, "with "+std::to_string(failures+1)+" attempts", 30),
    textLevel(fontTit, "level "+std::to_string(level), 33){
        title.setCharacterSize(80);
        std::vector<std::string> labels;
        utils::centerOrigin(textAttempts); utils::centerOrigin(textLevel);
        if(gameover){
            title.setString("Failed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            textLevel.setPosition({title.getPosition().x, title.getPosition().y+100.0f});
            labels={"Play again", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(fontOpt, labels[i], 24);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 490.0f + static_cast<float>(i) * 80.0f});
                options.push_back(option);
            }
        }
        else{
            title.setString("Passed!");
            utils::centerOrigin(title);
            title.setPosition({utils::width/2.0f, 150.0f});
            textAttempts.setPosition({title.getPosition().x, title.getPosition().y+100.0f});
            labels={"Next level", "Exit"};
            for(std::size_t i=0; i<labels.size(); i++){
                sf::Text option(fontOpt, labels[i], 24);
                utils::centerOrigin(option);
                option.setPosition({utils::width/2.0f, 490.0f + static_cast<float>(i) * 80.0f});
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
            if(selectedIndex==0){
                if(gameover){   //play again si richiama sullo stesso livello
                    game.changeState(std::make_unique<PlayingState>(game, level, ++failures));
                }
                else{   //si avanza di livello, ++level e azzeriamo i fallimenti
                    game.changeState(std::make_unique<PlayingState>(game, ++level, 0));
                }
            }
            else if(selectedIndex==1){
                if(gameover) game.requestClose(--level);   //dato che il livello da caricare è il succesivo, in caso avessimo perso, rimaniamo a level con --
                else game.requestClose(level);
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
    if(gameover) window.draw(textLevel); 
    else{
        window.draw(textAttempts);
    }
}





