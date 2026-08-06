#include "SFML/Graphics.hpp"

class Game;
class State;

class PlayingState : public State{
    Game& game;
    public:
    explicit PlayingState(Game& g);
    ~PlayingState();
};
