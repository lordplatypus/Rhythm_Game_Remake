#ifndef RESERVE_TANK_H_
#define RESERVE_TANK_H_
#include "Item.h"

class ReserveTank : public Item
{
public:
    ReserveTank(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);

private:
    void Effect() override;
};

#endif