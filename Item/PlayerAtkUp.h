#ifndef PLAYER_ATK_UP_H_
#define PLAYER_ATK_UP_H_
#include "Item.h"

class PlayerAtkUp : public Item
{
public:
    PlayerAtkUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    void Draw(sf::RenderWindow& render_window) const override;

private:
    void Effect() override;
};

#endif