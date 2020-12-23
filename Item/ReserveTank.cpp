#include "ReserveTank.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

ReserveTank::ReserveTank(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "ReserveTank";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    sprite_ = LP::SetSprite(item_reserve_tank_texture, position_);
    text_ = LP::SetText("Double HP, Can't Heal: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32);
    LP::SetTextScale(text_, 0.1f, 0.1f);
}

ReserveTank::~ReserveTank()
{
    LP::DeleteSprite(sprite_);
    LP::DeleteText(text_);
}

void ReserveTank::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void ReserveTank::Draw(const sf::RenderWindow& render_window)
{
    LP::DrawSprite(sprite_);
}

void ReserveTank::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        LP::DrawText(text_);
    }
}

void ReserveTank::Effect()
{
    playerManager_->AddMaxHP(playerManager_->GetMaxHP());
    playerManager_->AddHP(playerManager_->GetMaxHP() / 2);
    playerManager_->SetHeal(false);
}