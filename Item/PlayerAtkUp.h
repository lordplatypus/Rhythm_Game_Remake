#ifndef PLAYER_ATK_UP_H_
#define PLAYER_ATK_UP_H_
#include "Item.h"

class PlayerAtkUp : public Item
{
public:
    PlayerAtkUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~PlayerAtkUp() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;
};

#endif