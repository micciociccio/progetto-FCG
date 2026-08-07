#include "SFML/Graphics.hpp"
#include "State.hpp"

class Game;

struct AttachedDot{
    sf::CircleShape shape;
    sf::Angle offset;   //posizione che evita il "collasso" dei cerchi durante la rotazione
};

class PlayingState : public State{
    Game& game;
    sf::CircleShape circle;
    std::vector<sf::CircleShape> waitingDots;
    std::optional<sf::CircleShape> flyingDot;
    std::vector<AttachedDot> attachedDots;
    sf::Angle roundRotation=sf::degrees(0.0f);
    unsigned numLvl;
    static constexpr float launchSpeed=600.0f;
    static constexpr float reloadSpeed=100.0f;
    static constexpr float rotationSpeed=150.0f;
    static constexpr float orbitRadius=134.0f;   //abbiamo circle a 228, la barriera a 360, e considerando la grandezza della pallina otteniamo 134
    public:
        explicit PlayingState(Game& g);
        ~PlayingState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
    private:
        void updateWaitingDots(float dt);
        void attachFlyingDot();
        bool checkCollision(const AttachedDot& dot);
};
