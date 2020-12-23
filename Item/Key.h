#ifndef KEY_H_
#define KEY_H_
#include "Item.h"
#include "../Event/FindKeys.h"

class Key : public Item
{
public:
    Key(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, FindKeys* keyEvent);

private:
    void Effect() override;

private:
    FindKeys* keyEvent_{nullptr};
};

#endif