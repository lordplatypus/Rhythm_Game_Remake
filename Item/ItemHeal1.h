#ifndef ITEM_HEAL_1_H_
#define ITEM_HEAL_1_H_
#include "Item.h"

class ItemHeal1 : public Item
{
public:
    ItemHeal1(sf::Vector2f position, int itemID, Scene *scene);
    ~ItemHeal1() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void Effect() override;
};

#endif