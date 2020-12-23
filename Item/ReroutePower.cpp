#include "ReroutePower.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

ReroutePower::ReroutePower(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "ReroutePower";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    // sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    // LP::SetRectangleColor(sprite_, 255, 0, 0, 255);
    text_ = LP::SetText("1 HP, +1 Attack: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void ReroutePower::Effect()
{
    playerManager_->SetAtk(playerManager_->GetAtk() + 1);
    playerManager_->SetMaxHPChangeBool(true);
    playerManager_->SubMaxHP(playerManager_->GetMaxHP() - 1);
    playerManager_->SetMaxHPChangeBool(false);
}