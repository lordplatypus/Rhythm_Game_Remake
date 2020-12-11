#ifndef RESERVE_TANK_H_
#define RESERVE_TANK_H_
#include "Item.h"

class ReserveTank : public Item
{
public:
    ReserveTank(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~ReserveTank() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;
};

#endif