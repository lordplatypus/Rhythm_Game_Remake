#ifndef ENEMY7_H_
#define ENEMY7_H_
#include <vector>
#include "Enemy.h"

class Enemy7 : public Enemy
{
public:
    Enemy7(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy7() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;

private:
    void FireMortar();
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;
    //Animations
    void AnimationHandle(float delta_time, float beat_time) override;
    //Don't run into walls
    void CheckMoveLocation();
    //DFS
    void DFSPriorityDirection(sf::Vector2f current, sf::Vector2f end);
    sf::Vector2f DFS(sf::Vector2f location, std::vector<sf::Vector2f> visited, sf::Vector2f end, int depth);
    void DFSFinish(sf::Vector2f current, sf::Vector2f end);

private:
    //DFS
    bool finish_{false};
    sf::Vector2f move1_;
    sf::Vector2f move2_;
    sf::Vector2f move3_;
    sf::Vector2f move4_;

    enum State{Rest, Active, Angery, Fire, Retreat};
    State state_ = Rest;

    bool hasMoved_{true};
    int beatCounter_{0};

    //For Animations
    int endFrame_{0};
};

#endif