#ifndef ITEM_ADD_HEART_H_
#define ITEM_ADD_HEART_H_
#include "Item.h"

class ItemAddHeart : public Item
{
public:
    ItemAddHeart(sf::Vector2f position, int itemID, Scene *scene);
    ~ItemAddHeart() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void Effect() override;

private:
};

#endif