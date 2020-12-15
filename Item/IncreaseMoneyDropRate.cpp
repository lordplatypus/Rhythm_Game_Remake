#include "IncreaseMoneyDropRate.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

IncreaseMoneyDropRate::IncreaseMoneyDropRate(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    gem_ = gem;
    tag_ = "Item";
    name_ = "IncreaseMoneyDropRate";
    HP_ = 1;
    priceTag_ = 300;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_horseshoe_texture, position_);
    text_ = LP::SetText("Increase Money Drop Rate: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

IncreaseMoneyDropRate::~IncreaseMoneyDropRate()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void IncreaseMoneyDropRate::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void IncreaseMoneyDropRate::Draw()
{
    LP::DrawSprite(sprite_);
}

void IncreaseMoneyDropRate::DelayedDraw()
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw();
        LP::DrawText(text_);
    }
}

void IncreaseMoneyDropRate::Effect()
{
    playerManager_->SubMoney(priceTag_);

    gem_->SetMoneyModifier(gem_->GetMoneyModifer() + 1);
}