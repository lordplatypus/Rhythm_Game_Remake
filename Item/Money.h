#ifndef MONEY_H_
#define MONEY_H_
#include "Item.h"

class Money : public Item
{
public:
    Money(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm);
    ~Money() override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;
    
private:
    void Effect();
    void SpriteSetUp();

private:
    int value_{0};
    std::vector<sf::Sprite> sprites_;
};

#endif