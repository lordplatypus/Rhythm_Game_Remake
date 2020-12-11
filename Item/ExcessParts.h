#ifndef EXCESS_PARTS_H_
#define EXCESS_PARTS_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class ExcessParts : public Item
{
public:
    ExcessParts(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);
    ~ExcessParts() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};
};

#endif