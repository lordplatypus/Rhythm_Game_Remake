#include "EnemiesOnFloorTakeDamage.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

EnemiesOnFloorTakeDamage::EnemiesOnFloorTakeDamage(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem, Scene* scene)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    lem_ = lem;
    scene_ = scene;
    tag_ = "Item";
    name_ = "EnemiesOnFloorTakeDamage";
    HP_ = 1;
    priceTag_ = 50;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_heal_texture, position_);
    text_ = LP::SetText("Enemies on this floor take 1 damage: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void EnemiesOnFloorTakeDamage::Effect()
{
    playerManager_->SubMoney(priceTag_);

    for (auto i : lem_->GetEnemyData())
    {
        scene_->FindGameObject(std::to_string(i->ID_), false, true)->TakeDamage(1);
    }
}