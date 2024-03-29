#include "PerceptionUp.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

PerceptionUp::PerceptionUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "Perception";
    HP_ = 1;
    priceTag_ = 100;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_range_texture, position_);
    text_ = LP::SetText("Range +1: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void PerceptionUp::Effect()
{
    playerManager_->SetPerception(playerManager_->GetPerception() + CellSize);
    playerManager_->SubMoney(priceTag_);
}