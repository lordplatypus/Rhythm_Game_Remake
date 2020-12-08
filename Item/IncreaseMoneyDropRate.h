#ifndef INCREASE_MONEY_DROP_RATE_H_
#define INCREASE_MONEY_DROP_RATE_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class IncreaseMoneyDropRate : public Item
{
public:
    IncreaseMoneyDropRate(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);
    ~IncreaseMoneyDropRate() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};
};

#endif