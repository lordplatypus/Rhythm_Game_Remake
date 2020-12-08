#include "TempEnemyDamage.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

TempEnemyDamage::TempEnemyDamage(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, LocalEnemyManager* lem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    lem_ = lem;
    tag_ = "Item";
    name_ = "TempEnemyDamage";
    HP_ = 1;
    priceTag_ = 50;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_heal_texture, position_);
    text_ = LP::SetText("Enemies on this floor take 1 damage: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

TempEnemyDamage::~TempEnemyDamage()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void TempEnemyDamage::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void TempEnemyDamage::Draw()
{
    LP::DrawSprite(sprite_);
}

void TempEnemyDamage::DelayedDraw()
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw();
        LP::DrawText(text_);
    }
}

void TempEnemyDamage::Effect()
{
}