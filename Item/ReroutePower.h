#ifndef REROUTE_POWER_H_
#define REROUTE_POWER_H_
#include "Item.h"

class ReroutePower : public Item
{
public:
    ReroutePower(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~ReroutePower() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void DelayedDraw(const sf::RenderWindow& render_window) override;

private:
    void Effect() override;
};

#endif