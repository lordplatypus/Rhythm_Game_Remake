#include "RemoveEnemyHealingOnFloor.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

RemoveEnemyHealingOnFloor::RemoveEnemyHealingOnFloor(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    lem_ = lem;
    tag_ = "Item";
    name_ = "RemoveEnemyHealingOnFloor";
    HP_ = 1;
    priceTag_ = 50;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_taser_texture, position_);
    text_ = LP::SetText("Removes Enemy Healing On This Floor: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void RemoveEnemyHealingOnFloor::Effect()
{
    playerManager_->SubMoney(priceTag_);

    lem_->SetTempHealModifier(false);
}