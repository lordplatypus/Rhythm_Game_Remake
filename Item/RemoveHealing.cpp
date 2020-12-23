#include "RemoveHealing.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

RemoveHealing::RemoveHealing(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, GlobalEnemyManager* gem)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    gem_ = gem;
    tag_ = "Item";
    name_ = "RemoveHealing";
    HP_ = 1;
    priceTag_ = 500;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_emp_texture, position_);
    text_ = LP::SetText("Removes Healing From Everything: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

RemoveHealing::~RemoveHealing()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void RemoveHealing::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void RemoveHealing::Draw(const sf::RenderWindow& render_window)
{
    LP::DrawSprite(sprite_);
}

void RemoveHealing::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        LP::DrawText(text_);
    }
}

void RemoveHealing::Effect()
{
    playerManager_->SubMoney(priceTag_);

    gem_->SetHealModifier(false);
    playerManager_->SetHeal(false);
}