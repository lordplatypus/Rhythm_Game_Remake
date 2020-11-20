#ifndef REDUCE_COOLDOWN_H_
#define REDUCE_COOLDOWN_H_
#include "Item.h"

class ReduceCooldown : public Item
{
public:
    ReduceCooldown(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~ReduceCooldown() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;
    
private:
    void Effect() override;
};

#endif