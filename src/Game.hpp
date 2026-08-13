#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelData.hpp"
#include <memory>
#include <vector>

class State;   //dichiarazione condivisa per il compile time

enum class SoundEffect : std::size_t{ // 0->DotShot, 1->lvlPassed, 2->lvlFailed
    DotShot,
    lvlPassed,
    lvlFailed
};

class Game{
    sf::RenderWindow window;
    sf::Texture textureBg;
    sf::Sprite background;
    std::unique_ptr<State> currentState;
    std::vector<LevelData> levelContainers;
    std::vector<sf::SoundBuffer> soundsBuffer;
    std::vector<sf::Sound> sounds;
    std::size_t userLvl;
    public:
        Game(unsigned width, unsigned height, const std::string& title);
        ~Game();
        void changeState(std::unique_ptr<State> newState);
        void run();
        void requestClose(std::size_t level);
        LevelData getLvlSetup(std::size_t lvl);
        void playSound(SoundEffect index);
};

