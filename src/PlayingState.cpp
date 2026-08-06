#include "PlayingState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "GraphicsUtils.hpp"

PlayingState::PlayingState(Game& g)
:   game(g),
    circle(55.0f),
    dotToAppend(-1),
    numLvl(0),
    pressed(false){
        circle.setOrigin({circle.getRadius(), circle.getRadius()});
        circle.setPosition({utils::width/2.0f, utils::height/3.5f});
        for(int i=0; i<8; i++){
            sf::CircleShape dot(8.0f);
            dot.setOrigin({dot.getRadius(), dot.getRadius()});
            float startY=utils::height-100.0f;
            dot.setPosition({utils::width/2.0f, startY + static_cast<float>(i) * 20.0f});
            dots.push_back(dot);
        }
}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Space){
            if(dotToAppend < static_cast<int>(dots.size() -1)) dotToAppend++;    
        }
    }
}

void PlayingState::update(float dt){
    float speed=600.0f;
    circle.rotate(sf::degrees(100.0f*dt));
    if(dotToAppend>=0 && dotToAppend<dots.size()){
        sf::Vector2f pos=dots[dotToAppend].getPosition();
        pos.y-=dt*speed;
        dots[dotToAppend].setPosition(pos);
    }   
}

void PlayingState::render(sf::RenderWindow& window){
    window.draw(circle);
    for(sf::CircleShape& dot : dots){
        window.draw(dot);
    }
}