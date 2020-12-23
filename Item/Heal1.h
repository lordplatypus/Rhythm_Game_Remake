#ifndef HEAL_1_H_
#define HEAL_1_H_
#include "Item.h"

class Heal1 : public Item
{
public:
    Heal1(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~Heal1() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void DelayedDraw(const sf::RenderWindow& render_window) override;

private:
    void Effect() override;
};

#endif