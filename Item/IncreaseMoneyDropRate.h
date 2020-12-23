#ifndef INCREASE_MONEY_DROP_RATE_H_
#define INCREASE_MONEY_DROP_RATE_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class IncreaseMoneyDropRate : public Item
{
public:
    IncreaseMoneyDropRate(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};
};

#endif