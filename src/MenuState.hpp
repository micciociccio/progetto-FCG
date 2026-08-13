#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <vector>

class Game;   //forward declaration

class MenuState : public State{
    Game& game;
    sf::Font fontTit, fontOpt;
    sf::Text title;
    std::vector<sf::Text> options;
    std::size_t selectedIndex=0, resumeLevel;
    public:
        explicit MenuState(Game& g, std::size_t resumeLvl);
        ~MenuState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};
