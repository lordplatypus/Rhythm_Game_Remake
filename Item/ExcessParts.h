#ifndef EXCESS_PARTS_H_
#define EXCESS_PARTS_H_
#include "Item.h"
#include "../Enemy/GlobalEnemyManager.h"

class ExcessParts : public Item
{
public:
    ExcessParts(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem);
    void Draw(sf::RenderWindow& render_window) const override;

private:
    void Effect() override;

private:
    GlobalEnemyManager* gem_{nullptr};

    sf::RectangleShape rect_;
};

#endif