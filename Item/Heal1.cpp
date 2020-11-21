#include "Heal1.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Heal1::Heal1(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "Heal";
    HP_ = 1;
    priceTag_ = 100;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetLeft(0);
    SetRight(imageWidth_);
    SetTop(0);
    SetBottom(imageHeight_);
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_heal_texture, position_);
}

Heal1::~Heal1()
{
    LP::DeleteSprite(sprite_);
}

void Heal1::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void Heal1::Draw()
{
    LP::DrawSprite(sprite_);
}

void Heal1::DelayedDraw()
{
    if (ifSeesPlayer_) arrow_->Draw();
}

void Heal1::Effect()
{
    playerManager_->AddHP(1);
    playerManager_->SubMoney(priceTag_);
}