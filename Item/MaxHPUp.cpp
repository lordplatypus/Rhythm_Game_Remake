#include "MaxHPUp.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

MaxHPUp::MaxHPUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "MaxHP";
    HP_ = 1;
    priceTag_ = 69;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetLeft(0);
    SetRight(imageWidth_);
    SetTop(0);
    SetBottom(imageHeight_);
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_maxHP_texture, position_);
}

MaxHPUp::~MaxHPUp()
{
    LP::DeleteSprite(sprite_);
}

void MaxHPUp::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void MaxHPUp::Draw()
{
    LP::DrawSprite(sprite_);
}

void MaxHPUp::DelayedDraw()
{
    if (ifSeesPlayer_) arrow_->Draw();
}

void MaxHPUp::Effect()
{
    playerManager_->AddMaxHP(1);
    playerManager_->SubMoney(priceTag_);
}