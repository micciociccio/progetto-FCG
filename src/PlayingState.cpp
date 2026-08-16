#include "PlayingState.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "MenuState.hpp"
#include "EndGameState.hpp"
#include "GameUtils.hpp"

PlayingState::PlayingState(Game& g, unsigned lvl, unsigned fails)
:   game(g),
    circle(70.0f),
    data(g.getLvlSetup(lvl)),
    level(lvl),
    failures(fails),
    textLvl(game.getGenFont(), "", 80), textAttempts(game.getGenFont(), "failures\n"+std::to_string(failures), 24),
    rs(data.rotationSpeed){
        circle.setOrigin({circle.getRadius(), circle.getRadius()});   //cerchio centrale
        circle.setPosition({utils::width/2.0f, utils::height/3.2f});
        circle.setTexture(&game.getTexture(Textures::Circle));
        for(int i=0; i<data.waitingD; i++){
            sf::CircleShape dot(14.0f);
            dot.setOrigin({dot.getRadius(), dot.getRadius()});
            float startY=utils::height-350.0f;
            dot.setPosition({utils::width/2.0f, startY + static_cast<float>(i) * 48.0f});
            dot.setTexture(&game.getTexture(Textures::Dot));
            waitingDots.push_back(dot);   //dots da aggiungere a circle
        }
        for(int i=0; i<data.attachedD; i++){   //dots già in rotazione su circle
            sf::CircleShape dot(14.0f);
            dot.setOrigin({dot.getRadius(), dot.getRadius()});
            dot.setTexture(&game.getTexture(Textures::Dot));
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            AttachedDot d={dot, data.offset*static_cast<float>(i), line};
            attachedDots.push_back(d);
        }
        // level=(lvl>utils::lastLvl) ? utils::lastLvl : lvl;   //evita di stampare valori a schermo errati ogni volta che si usa level
        textLvl.setString(std::to_string(level));
        utils::centerOrigin(textLvl); utils::centerOrigin(textAttempts);
        textLvl.setPosition({circle.getPosition().x, circle.getPosition().y});
        textAttempts.setLineAlignment(sf::Text::LineAlignment::Center);
        textAttempts.setPosition({140.0f, utils::height-70.0f});
}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const sf::Event& event){
    if(const auto* keyPressed=event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code==sf::Keyboard::Key::Space && !flyingDot && !waitingDots.empty()){
            flyingDot=waitingDots.front();
            waitingDots.erase(waitingDots.begin());
            game.playSound(SoundEffect::DotShot);
        }
        else if(keyPressed->code==sf::Keyboard::Key::Escape){
            game.changeState(std::make_unique<MenuState>(game));
        }
    }
}

void PlayingState::update(float dt){
    //player ha schiacciato Space dobbiamo far muovere il dot corrente
    if(flyingDot){
        sf::Vector2f pos=flyingDot->getPosition();
        pos.y-=dt*launchSpeed;
        flyingDot->setPosition(pos);
        if(pos.y<=390.0f){
            pos.y=390.0f;
            flyingDot->setPosition(pos);
            if(attachFlyingDot()) return;
        } 
    }
    //aggiornamento della coda di dots
    updateWaitingDots(dt);
    //rotazione ad ogni frame dei dots attacheds
    if(data.changeRS){   //implementazione casuale del cambio di velocità
        speedTimer+=dt;
        if(speedTimer>=changeInterval){
            speedTimer=0.0f;
            std::uniform_real_distribution<float> dis(data.rotationSpeed*data.minRS, data.rotationSpeed*data.maxRS);
            rs=dis(gen);
            if(data.changeRD){   //implementazione del cambio casuale di verso rotazione
                std::uniform_int_distribution<int> dirDis(0, 1);
                direction=(dirDis(gen)==0)? -1.0 : 1.0;
            }
            rs=dis(gen)*direction;
        }
    }  
    roundRotation+=sf::degrees(dt*rs);
    sf::Vector2f center=circle.getPosition();
    for(AttachedDot& dot : attachedDots){
        sf::Angle totalAngle=roundRotation+dot.offset;
        float updateX=center.x+orbitRadius*std::cos(totalAngle.asRadians());   //orbita del dot (centro del circle)
        float updateY=center.y+orbitRadius*std::sin(totalAngle.asRadians());
        sf::Vector2f pos{updateX, updateY};
        updateX=center.x+(orbitRadius-dot.shape.getRadius())*std::cos(totalAngle.asRadians());   //orbita del vertex collegato al dot (punto sulla circonferenza del circle, sottraiamo radius)
        updateY=center.y+(orbitRadius-dot.shape.getRadius())*std::sin(totalAngle.asRadians());
        dot.line[0].position={updateX, updateY};
        updateX=center.x+(orbitRadius-circle.getRadius())*std::cos(totalAngle.asRadians());   //orbita del vertex esterno al circle, sottraiamo infatti il raggio dal centro
        updateY=center.y+(orbitRadius-circle.getRadius())*std::sin(totalAngle.asRadians());
        dot.line[1].position={updateX, updateY};
        dot.shape.setPosition(pos);
    }
}

void PlayingState::render(sf::RenderWindow& window){
    window.draw(circle);
    window.draw(textLvl);
    window.draw(textAttempts);
    for(sf::CircleShape& dot : waitingDots){
        window.draw(dot);
    }
    for(AttachedDot& dot : attachedDots){
        window.draw(dot.shape);
        window.draw(dot.line);
    }
    if(flyingDot) window.draw(*flyingDot);
}

void PlayingState::updateWaitingDots(float dt){
    for(size_t i=0; i<waitingDots.size(); i++){
        sf::Vector2f pos=waitingDots[i].getPosition();
        float targetY=utils::height-350.0f + static_cast<float>(i) * 48.0f;
        if(pos.y>targetY){
            pos.y=std::max(targetY, pos.y-dt*reloadSpeed);   //se va oltre il target, assegnamo targetY così che non si muova più
            waitingDots[i].setPosition(pos);
        }
    }
}

bool PlayingState::attachFlyingDot(){   //return true solo in caso di changeState() che distrugge lo stato corrente per propagare il cambio
    sf::Vector2f center=circle.getPosition();
    sf::Vector2f toDot=flyingDot->getPosition()-center;
    sf::Angle absoluteAngle=sf::radians(std::atan2(toDot.y, toDot.x));
    AttachedDot newDot{*flyingDot, absoluteAngle-roundRotation};   //offset relativo, in modo che rimanga in quel punto della rotazione
    if(checkCollision(newDot)){   //caso 1: gameover il dot ha colpito gli altri in orbita
        game.playSound(SoundEffect::lvlFailed);
        game.changeState(std::make_unique<EndGameState>(game, true, level, failures));
        return true; 
    }
    else if(waitingDots.empty()){   //caso 2: se non c'è collisione && abbiamo finito i dot da inserire abbiamo vinto
        game.playSound(SoundEffect::lvlPassed);
        game.changeState(std::make_unique<EndGameState>(game, false, level, failures)); //livello completato
        return true;
    }
    //dot inserito correttamente, altri da lanciare
    //linea collegata dal centro al dot
    sf::VertexArray linea(sf::PrimitiveType::Lines, 2);
    linea[0].position={utils::width/2.0f, 390.0f-newDot.shape.getRadius()};   //vertex sul dot, ovvero partenza dalla barriera - raggio per limite circonferenza circle 
    linea[1].position={utils::width/2.0f, 320.0f};   //position di circle + 70 radius = 250 + 70 = 320
    newDot.line=linea;
    attachedDots.push_back(newDot);
    flyingDot.reset();   //torna vuoto, Space ora funziona
    return false;    
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