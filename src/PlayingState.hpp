#include "SFML/Graphics.hpp"
#include "State.hpp"

class Game;

class PlayingState : public State{
    Game& game;
    sf::CircleShape circle;
    std::vector<sf::CircleShape> dots;
    int dotToAppend;
    unsigned numLvl;
    bool pressed;
    public:
        explicit PlayingState(Game& g);
        ~PlayingState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
};
