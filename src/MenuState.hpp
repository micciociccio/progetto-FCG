#include "SFML/Graphics.hpp"
#include "State.hpp"
#include <vector>

class Game;   //forward declaration

class MenuState : public State{
    Game& game;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    int selectedIndex=0;
    void centerOrigin(sf::Text& t);
    public:
        explicit MenuState(Game& g);
        ~MenuState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};
