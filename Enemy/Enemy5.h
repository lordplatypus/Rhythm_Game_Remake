#ifndef ENEMY5_H_
#define ENEMY5_H_
#include <vector>
#include "Enemy.h"

class Enemy5 : public Enemy
{
public:
    Enemy5(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy5() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;
    void ReactOnCollision(GameObject& other) override;
    void TakeDamage(const int damage) override;
    
private:
    void AnimationHandle(float delta_time, float beat_time) override;
    void CheckMoveLocation();
    void SpawnPawn();

private:
    enum State{Normal, Angry};
    State state_ = Normal;

    int enemyRectangle_{0}; //temp until I make sprite
    bool hasMoved_{true};
    int pawnID{100};
};

#endif