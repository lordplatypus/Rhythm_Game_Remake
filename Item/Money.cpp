#include "Money.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Money::Money(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm)
{
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    tag_ = "Item";
    name_ = "Money";
    HP_ = 1;
    value_ = rand() % 10 + 1;
    imageWidth_ = 32;
    imageHeight_ = 32;
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    SpriteSetUp();

    // scene_->GetUI()->AddUIArrow(position_, ID_, HP_);
    // scene_->GetUI()->AddUIText(ID_, LP::SetText("Parts: " + std::to_string(value_), sf::Vector2f(position_.x, position_.y - 4), 32));
    // scene_->GetUI()->FindUIText(ID_)->SetTextScale(0.1f);
}

Money::~Money()
{
    sprites_.clear();
    //delete arrow_;
}

void Money::Draw(sf::RenderWindow& render_window) const
{
    for (auto i : sprites_) render_window.draw(i);
}

void Money::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (ifSeesPlayer_) 
        arrow_->Draw(render_window);
}

void Money::Effect()
{
    playerManager_->AddMoney(value_);
}

void Money::SpriteSetUp()
{
    for (int i = 0; i < value_; i++)
    {
        int textureID = part_screw_texture;
        switch(rand() % 4)
        {
            case 0:
            textureID = part_nut_texture;
            break;

            case 1:
            textureID = part_battery_texture;
            break;

            case 2:
            textureID = part_spring_texture;
            break;

            case 3:
            textureID = part_dark_spring_texture;
            break;
        }
        sf::Vector2f spritePosition{position_.x + rand() % 32, position_.y + rand() % 32};
        sprites_.push_back(LP::SetSprite(textureID, spritePosition));
        LP::SetSpriteOriginCenter(&sprites_[i]);
    }
}