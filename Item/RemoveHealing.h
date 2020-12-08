#ifndef REMOVE_HEALING_H_
#define REMOVE_HEALING_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class RemoveHealing : public Item
{
public:
    RemoveHealing(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);
    ~RemoveHealing() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};
};

#endif