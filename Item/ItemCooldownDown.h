#ifndef ITEM_COOLDOWN_DOWN_H_
#define ITEM_COOLDOWN_DOWN_H_
#include "Item.h"

class ItemCooldownDown : public Item
{
public:
    ItemCooldownDown(sf::Vector2f position, int itemID, Scene *scene);
    ~ItemCooldownDown() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void Effect() override;

private:
};

#endif