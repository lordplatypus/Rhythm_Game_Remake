#ifndef ENEMY3_H_
#define ENEMY3_H_
#include <vector>
#include "Enemy.h"

class Enemy3 : public Enemy
{
public:
    Enemy3(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy3() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;
    void ReactOnCollision(GameObject& other) override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;

private:
    void AnimationHandle(float delta_time, float beat_time) override;
    void CheckMoveLocation();

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

    enum State{Rest, Normal};
    State state_ = Rest;

    bool hasMoved_{true};
    int beatCounter_{0};

    bool delayAttack_{false};
    int delayMoveX_{0};
    int delayMoveY_{0};
};

#endif