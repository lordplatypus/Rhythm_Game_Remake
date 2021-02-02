#include "PlayerAtkUp.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

PlayerAtkUp::PlayerAtkUp(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "PlayerAtkUp";
    HP_ = 1;
    priceTag_ = 80;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setPosition(position_);
    rect_.setFillColor(sf::Color::Yellow);
    text_ = LP::SetText("Increase Player Atk Damage By 1: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void PlayerAtkUp::Draw(sf::RenderWindow& render_window) const
{
    render_window.draw(rect_);
}

void PlayerAtkUp::Effect()
{
    playerManager_->SubMoney(priceTag_);

    playerManager_->SetAtk(playerManager_->GetAtk() + 1);
}