#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelData.hpp"
#include <memory>
#include <vector>
#include <iostream>

class State;   //dichiarazione condivisa per il compile time

enum class SoundEffect{ // 0->DotShot, 1->MenuSelect, 2->LvlPassed, 3->LvlFailed
    DotShot,
    MenuSelect,
    LvlPassed,
    LvlFailed
};

enum class Fonts{   //general, title and Num fonts
    Title,
    Num,
    Gen
};

enum class Textures{
    Dot,
    Circle
};

class Game{
    sf::RenderWindow window;
    sf::Texture textureBg, dotTexture, circleTexture;
    sf::Sprite background;
    std::unique_ptr<State> currentState;
    std::vector<LevelData> levelContainers;
    std::vector<sf::SoundBuffer> soundsBuffer;
    std::vector<sf::Sound> sounds;
    unsigned userLvl;
    sf::Font titleFont, genFont, numFont;   
    //font caricati una sola volta dal file al quale fanno riferimento tutti gli :State 
    public:
        Game(unsigned width, unsigned height, const std::string& title);
        ~Game();
        void changeState(std::unique_ptr<State> newState);
        void run();
        void requestClose();
        LevelData getLvlSetup(unsigned lvl);
        void playSound(SoundEffect index);
        unsigned getUserLvl();
        void updateUserLvl(unsigned newLvl);
        const sf::Texture& getTexture(Textures t);
        const sf::Font& getFont(Fonts f);
};

