#pragma once
#include "SFML/Graphics.hpp"

namespace utils{
    
    inline constexpr float width=480;
    inline constexpr float height=800;

    inline void centerOrigin(sf::Text& t){
        sf::FloatRect bounds=t.getLocalBounds();
        t.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    }
}
