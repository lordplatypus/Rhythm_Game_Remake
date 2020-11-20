#ifndef MONEY_H_
#define MONEY_H_
#include "Item.h"

class Money : public Item
{
public:
    Money(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~Money() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    
private:
    void Effect();
    void SpriteSetUp();

private:
    int value_{0};
    std::vector<int> sprites_;
};

#endif