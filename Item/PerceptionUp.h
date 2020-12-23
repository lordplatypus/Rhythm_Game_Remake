#ifndef PERCEPTION_UP_H_
#define PERCEPTION_UP_H_
#include "Item.h"

class PerceptionUp : public Item
{
public:
    PerceptionUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);

private:
    void Effect() override;

private:
    const int CellSize{32};
};

#endif