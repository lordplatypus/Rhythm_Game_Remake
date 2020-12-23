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
    priceTag_ = 200;
    imageWidth_ = 32;
    imageHeight_ = 32;
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_range_texture, position_);
    text_ = LP::SetText("Range +1: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

PerceptionUp::~PerceptionUp()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void PerceptionUp::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void PerceptionUp::Draw(const sf::RenderWindow& render_window)
{
    LP::DrawSprite(sprite_);
}

void PerceptionUp::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        LP::DrawText(text_);
    }
}

void PerceptionUp::Effect()
{
    playerManager_->SetPerception(playerManager_->GetPerception() + CellSize);
    playerManager_->SubMoney(priceTag_);
}