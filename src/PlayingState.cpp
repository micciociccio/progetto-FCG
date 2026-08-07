#include "PlayingState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "GraphicsUtils.hpp"

PlayingState::PlayingState(Game& g)
:   game(g),
    circle(70.0f),
    numLvl(0){
        circle.setOrigin({circle.getRadius(), circle.getRadius()});   //cerchio centrale
        circle.setPosition({utils::width/2.0f, utils::height/3.5f});
        for(int i=0; i<5; i++){
            sf::CircleShape dot(14.0f);
            dot.setOrigin({dot.getRadius(), dot.getRadius()});
            float startY=utils::height-100.0f;
            dot.setPosition({utils::width/2.0f, startY + static_cast<float>(i) * 38.0f});
            waitingDots.push_back(dot);   //dots da aggiungere al cerchio
        }
}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Space && !flyingDot && !waitingDots.empty()){
            flyingDot=waitingDots.front();
            waitingDots.erase(waitingDots.begin());
        }
    }
}

void PlayingState::update(float dt){
    //player ha schiacciato Space dobbiamo far muovere il dot corrente
    if(flyingDot){
        sf::Vector2f pos=flyingDot->getPosition();
        pos.y-=dt*launchSpeed;
        flyingDot->setPosition(pos);
        updateWaitingDots(dt);
        if(pos.y<=360.0f){
            pos.y=360.0f;
            flyingDot->setPosition(pos);
            attachFlyingDot();
        } 
    }
    //rotazione ad ogni frame dei dots attacheds  
    roundRotation+=sf::degrees(dt*rotationSpeed);
    sf::Vector2f center=circle.getPosition();
    for(AttachedDot& dot : attachedDots){
        sf::Angle totalAngle=roundRotation+dot.offset;
        sf::Vector2f pos{
            center.x+orbitRadius*std::cos(totalAngle.asRadians()),
            center.y+orbitRadius*std::sin(totalAngle.asRadians())
        };
        dot.shape.setPosition(pos);
    }
}

void PlayingState::render(sf::RenderWindow& window){
    window.draw(circle);
    for(sf::CircleShape& dot : waitingDots){
        window.draw(dot);
    }
    for(AttachedDot& dot : attachedDots){
        window.draw(dot.shape);
    }
    if(flyingDot) window.draw(*flyingDot);
}

void PlayingState::updateWaitingDots(float dt){
    for(size_t i=0; i<waitingDots.size(); i++){
        sf::Vector2f pos=waitingDots[i].getPosition();
        float targetY=utils::height-100.0f+static_cast<float>(i)*38.0f;
        if(pos.y>targetY){
            pos.y=std::max(targetY, pos.y-dt*reloadSpeed);   //se va oltre il target, assegnamo targetY così che non si muova più
            waitingDots[i].setPosition(pos);
        }
    }
}

void PlayingState::attachFlyingDot(){
    sf::Vector2f center=circle.getPosition();
    sf::Vector2f toDot=flyingDot->getPosition()-center;
    sf::Angle absoluteAngle=sf::radians(std::atan2(toDot.y, toDot.x));
    AttachedDot newDot{*flyingDot, absoluteAngle-roundRotation};   //offset relativo, in modo che rimanga in quel punto della rotazione
    if(checkCollision(newDot)){
        game.changeState(std::make_unique<MenuState>(game));
        return;
    }
    else{
        // if(waitingDots.empty()) game.changeState(std::make_unique<PlayingState>(game)); livello completato
    }
    attachedDots.push_back(newDot);
    flyingDot.reset();   //torna vuoto, Space ora funziona
}

bool PlayingState::checkCollision(const AttachedDot& dot){
    for(size_t i=0; i<attachedDots.size(); i++){
        sf::Vector2f diff=dot.shape.getPosition()-attachedDots[i].shape.getPosition();
        float distance=std::sqrt(diff.x*diff.x+diff.y*diff.y);
        float sumRad=dot.shape.getRadius()+attachedDots[i].shape.getRadius();
        if(distance<=sumRad) return true;
    }
    return false;
}