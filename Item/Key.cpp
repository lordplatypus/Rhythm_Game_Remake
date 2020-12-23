#include "Key.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Key::Key(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, FindKeys* keyEvent)
{
    playerManager_ = playerManager;
    pm_ = pm;
    keyEvent_ = keyEvent;
    position_ = position;
    tag_ = "Item";
    name_ = "Key";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    //sprite_ = LP::SetSprite(item_heal_texture, position_);
    // sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    // LP::SetRectangleColor(sprite_, 100, 100, 0, 255);
}

void Key::Effect()
{
    keyEvent_->PickUpKey();
}