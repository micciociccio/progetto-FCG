#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <vector>

class Game;   //forward declaration

class MenuState : public State{
    Game& game;
    sf::Text title;
    std::vector<sf::Text> options;
    unsigned selectedIndex=0, userLevel;
    public:
        explicit MenuState(Game& g);
        ~MenuState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};
