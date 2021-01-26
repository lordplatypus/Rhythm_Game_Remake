#include "ReroutePower.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

ReroutePower::ReroutePower(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "ReroutePower";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setPosition(position_);
    rect_.setFillColor(sf::Color::Magenta);
    text_ = LP::SetText("1 HP, +1 Attack: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32, sf::Vector2f(0.1f, 0.1f));
}

void ReroutePower::Draw(sf::RenderWindow& render_window) const
{
    render_window.draw(rect_);
}

void ReroutePower::Effect()
{
    playerManager_->SetAtk(playerManager_->GetAtk() + 1);
    playerManager_->SetMaxHPChangeBool(true);
    playerManager_->SubMaxHP(playerManager_->GetMaxHP() - 1);
    playerManager_->SetMaxHPChangeBool(false);
}