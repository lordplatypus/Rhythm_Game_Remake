#ifndef MAX_HP_UP_H_
#define MAX_HP_UP_H_
#include "Item.h"

class MaxHPUp : public Item
{
public:
    MaxHPUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);

private:
    void Effect() override;
};

#endif