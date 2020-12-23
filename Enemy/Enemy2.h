#ifndef ENEMY2_H_
#define ENEMY2_H_
#include "Enemy.h"

class Enemy2 : public Enemy
{
public:
    Enemy2(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Enemy2() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void DelayedDraw(const sf::RenderWindow& render_window) override;

private:
    void CheckMoveLocation();
    void ReactOnCollision(GameObject& other) override;

private:
    int enemy2Rect_{0};
    bool hasMoved_{true};
    bool movedDown_{false};
    int beatCount_{0};
    bool delayAttack_{false};
};

#endif