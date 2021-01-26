#ifndef REDUCE_COOLDOWN_H_
#define REDUCE_COOLDOWN_H_
#include "Item.h"

class ReduceCooldown : public Item
{
public:
    ReduceCooldown(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    
private:
    void Effect() override;
};

#endif