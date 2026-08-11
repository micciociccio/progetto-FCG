#pragma once
#include "SFML/Graphics.hpp"

struct LevelData{   //con '=' assegnamo i valori di default per il fallback
    unsigned waitingD=2;
    unsigned attachedD=0;
    sf::Angle offset;
    float rotationSpeed=120.0f;
    bool changeRS=false;   //rotazione a velocità variabile
    float minRS;
    float maxRS;
    bool changeRD=false;   //cambio del verso di rotazione
};