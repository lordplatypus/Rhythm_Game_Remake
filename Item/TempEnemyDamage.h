#ifndef TEMP_ENEMY_DAMAGE_H_
#define TEMP_ENEMY_DAMAGE_H_
#include "Item.h"
#include "../Enemy/LocalEnemyManager.h"

class TempEnemyDamage : public Item
{
public:
    TempEnemyDamage(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem);
    ~TempEnemyDamage() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    LocalEnemyManager* lem_{nullptr};
};

#endif