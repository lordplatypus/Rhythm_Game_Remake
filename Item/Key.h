#ifndef KEY_H_
#define KEY_H_
#include "Item.h"
#include "../Event/FindKeys.h"

class Key : public Item
{
public:
    Key(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, FindKeys* keyEvent);
    ~Key() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;

private:
    void Effect() override;

private:
    FindKeys* keyEvent_{nullptr};
};

#endif