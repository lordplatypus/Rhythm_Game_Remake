#include "ExcessParts.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

ExcessParts::ExcessParts(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    gem_ = gem;
    tag_ = "Item";
    name_ = "ExcessParts";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    // sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    // LP::SetRectangleColor(sprite_, 255, 0, 0, 255);
    text_ = LP::SetText("Start At Square 1 But With Some Extra Parts: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void ExcessParts::Effect()
{
    playerManager_->AddMoney(1000);
    playerManager_->SetAtk(1);
    playerManager_->SubMaxHP(playerManager_->GetMaxHP() - 1);
    playerManager_->SetPerception(32);
    //gem_->SetMoneyModifier(5);
}