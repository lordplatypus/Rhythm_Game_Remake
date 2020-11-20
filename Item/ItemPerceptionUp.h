#ifndef ITEM_PERCEPTION_UP_H_
#define ITEM_PERCEPTION_UP_H_
#include "Item.h"

class ItemPerceptionUp : public Item
{
public:
    ItemPerceptionUp(sf::Vector2f position, int itemID, Scene *scene);
    ~ItemPerceptionUp() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void Effect() override;
};

#endif