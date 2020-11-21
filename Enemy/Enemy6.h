#ifndef ENEMY6_H_
#define ENEMY6_H_
#include <vector>
#include "Enemy.h"

class Enemy6 : public Enemy
{
public:
    Enemy6(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy6() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;
    void ReactOnCollision(GameObject& other) override;
    void TakeDamage(const int damage) override;

private:
    void AnimationHandle(float delta_time, float beat_time) override;
    void CheckMoveLocation();
    void TeleportToPlayer();

    void DFSPriorityDirection(sf::Vector2f current, sf::Vector2f end);
    sf::Vector2f DFS(sf::Vector2f location, std::vector<sf::Vector2f> visited, sf::Vector2f end, int depth);
    void DFSFinish(sf::Vector2f current, sf::Vector2f end);

private:
    enum State{Normal, Angry};
    State state_{Normal};

    bool hasMoved_ = true;
    //0=left, 1=right, 2=up, 3=down
    int direction_;

    bool delayAttack_ = false;
    int delayMoveX_ = 0;
    int delayMoveY_ = 0;

    //DFS
    bool finish_ = false;
    sf::Vector2f move1_;
    sf::Vector2f move2_;
    sf::Vector2f move3_;
    sf::Vector2f move4_;
};

#endif