#ifndef ENEMY1_H_
#define ENEMY1_H_
#include <vector>
#include "Enemy.h"

class Enemy1 : public Enemy
{
public:
    Enemy1(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy1() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;

private:
    void ReactOnCollision(GameObject& other) override;
    void AnimationHandle(float delta_time, float beat_time) override;

private:
    bool hasMoved_{true};
};

#endif