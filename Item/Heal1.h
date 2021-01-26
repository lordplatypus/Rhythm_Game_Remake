#ifndef HEAL_1_H_
#define HEAL_1_H_
#include "Item.h"

class Heal1 : public Item
{
public:
    Heal1(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);

private:
    void Effect() override;
};

#endif