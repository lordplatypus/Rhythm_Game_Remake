#ifndef MAX_HP_UP_H_
#define MAX_HP_UP_H_
#include "Item.h"

class MaxHPUp : public Item
{
public:
    MaxHPUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~MaxHPUp() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;
};

#endif