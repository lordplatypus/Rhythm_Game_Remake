#include "BlindLuck.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

BlindLuck::BlindLuck(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    gem_ = gem;
    tag_ = "Item";
    name_ = "BlindLuck";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_sunglassese_texture, position_);
    text_ = LP::SetText("Limited View But Money Drops More Fequent: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

BlindLuck::~BlindLuck()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void BlindLuck::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void BlindLuck::Draw(const sf::RenderWindow& render_window)
{
    LP::DrawSprite(sprite_);
}

void BlindLuck::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        LP::DrawText(text_);
    }
}

void BlindLuck::Effect()
{
    playerManager_->SetPerception(32);
    playerManager_->SetPerceptionChangeBool(false);
    gem_->SetMoneyModifier(5);
}