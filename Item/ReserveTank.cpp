#include "ReserveTank.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

ReserveTank::ReserveTank(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "ReserveTank";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_reserve_tank_texture, position_);
    text_ = LP::SetText("Double HP, Can't Heal: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void ReserveTank::Effect()
{
    playerManager_->AddMaxHP(playerManager_->GetMaxHP());
    playerManager_->AddHP(playerManager_->GetMaxHP() / 2);
    playerManager_->SetHeal(false);
}