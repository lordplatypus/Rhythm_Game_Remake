#ifndef PERCEPTION_UP_H_
#define PERCEPTION_UP_H_
#include "Item.h"

class PerceptionUp : public Item
{
public:
    PerceptionUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~PerceptionUp() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    const int CellSize{32};
};

#endif