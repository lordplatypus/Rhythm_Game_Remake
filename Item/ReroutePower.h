#ifndef REROUTE_POWER_H_
#define REROUTE_POWER_H_
#include "Item.h"

class ReroutePower : public Item
{
public:
    ReroutePower(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);

private:
    void Effect() override;
};

#endif