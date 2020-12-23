#ifndef REMOVE_ENEMY_HEALING_ON_FLOOR_H_
#define REMOVE_ENEMY_HEALING_ON_FLOOR_H_
#include "Item.h"
#include "../Enemy/LocalEnemyManager.h"

class RemoveEnemyHealingOnFloor : public Item
{
public:
    RemoveEnemyHealingOnFloor(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem);
    ~RemoveEnemyHealingOnFloor() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void DelayedDraw(const sf::RenderWindow& render_window) override;

private:
    void Effect() override;

private:
    LocalEnemyManager* lem_{nullptr};
};

#endif