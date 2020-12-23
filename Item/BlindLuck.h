#ifndef BLIND_LUCK_H_
#define BLIND_LUCK_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class BlindLuck : public Item
{
public:
    BlindLuck(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);
    ~BlindLuck() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void DelayedDraw(const sf::RenderWindow& render_window) override;

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};
};

#endif