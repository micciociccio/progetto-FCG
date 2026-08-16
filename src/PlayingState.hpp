#include "SFML/Graphics.hpp"
#include "State.hpp"
#include "LevelData.hpp" 
#include <random>
#include <string>

class Game;

struct AttachedDot{
    sf::CircleShape shape;
    sf::Angle offset;   //posizione che evita il "collasso" dei cerchi durante la rotazione
    sf::VertexArray line;  
};

class PlayingState : public State{
    Game& game;
    sf::CircleShape circle;
    std::vector<sf::CircleShape> waitingDots;
    std::optional<sf::CircleShape> flyingDot;
    LevelData data;
    unsigned level, failures;
    sf::Text textLvl, textAttempts;
    std::vector<AttachedDot> attachedDots;
    sf::Angle roundRotation=sf::degrees(0.0f);
    float rs;
    float speedTimer=0.0f;
    float changeInterval=1.5f;
    float direction=1.0f;   //default direction "monoverso"
    std::mt19937 gen{std::random_device{}()}; 
    static constexpr float launchSpeed=600.0f;
    static constexpr float reloadSpeed=220.0f;
    // static constexpr float rotationSpeed=120.0f;
    static constexpr float orbitRadius=140.0f;   //abbiamo circle a posizione.y=250, la "barriera" a y=390 otteniamo 140
    public:
        explicit PlayingState(Game& g, unsigned lvl, unsigned fails);
        ~PlayingState();
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
    private:
        void updateWaitingDots(float dt);
        bool attachFlyingDot();
        bool checkCollision(const AttachedDot& dot);
};
