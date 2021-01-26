#ifndef ENEMIES_ON_FLOOR_TAKE_DAMAGE_H_
#define ENEMIES_ON_FLOOR_TAKE_DAMAGE_H_
#include "Item.h"
#include "../Enemy/LocalEnemyManager.h"

class EnemiesOnFloorTakeDamage : public Item
{
public:
    EnemiesOnFloorTakeDamage(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem, Scene* scene);

private:
    void Effect() override;

private:
    LocalEnemyManager* lem_{nullptr};
};

#endif