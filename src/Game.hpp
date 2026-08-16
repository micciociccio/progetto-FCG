#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelData.hpp"
#include <memory>
#include <vector>
#include <iostream>

class State;   //dichiarazione condivisa per il compile time

enum class SoundEffect : std::size_t{ // 0->DotShot, 1->lvlPassed, 2->lvlFailed
    DotShot,
    lvlPassed,
    lvlFailed
};

enum class Textures : std::size_t{
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
    std::size_t userLvl;
    sf::Font genFont, titleFont;   //general and title fonts
    //font caricati una sola volta dal file a cui fanno riferimento tutti gli :State 
    public:
        Game(unsigned width, unsigned height, const std::string& title);
        ~Game();
        void changeState(std::unique_ptr<State> newState);
        void run();
        void requestClose();
        LevelData getLvlSetup(std::size_t lvl);
        void playSound(SoundEffect index);
        unsigned getUserLvl();
        void updateUserLvl(unsigned newLvl);
        const sf::Texture& getTexture(Textures t);
        const sf::Font& getTitleFont();
        const sf::Font& getGenFont();
};

