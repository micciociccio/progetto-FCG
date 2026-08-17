#pragma once
#include "SFML/Graphics.hpp"

namespace utils{
    
    inline constexpr float width=480;
    inline constexpr float height=800;

    inline constexpr unsigned lastLvl=10;

    inline void centerOrigin(sf::Text& t){
        sf::FloatRect bounds=t.getLocalBounds();
        t.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    }

    inline void updateColors(std::vector<sf::Text>& v, std::size_t index){
        for(std::size_t i=0; i<v.size(); i++){
            if(i==index){
                v[i].setFillColor(sf::Color::Red);
            }
            else v[i].setFillColor(sf::Color::White);
        }
    }

    inline void makeBorder(sf::Text& t, float value, sf::Color color){
        t.setOutlineThickness(value);
        t.setOutlineColor(color);
    }
}
