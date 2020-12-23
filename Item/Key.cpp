#include "Key.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Key::Key(sf::Vector2f position, PlayerManager* playerManager, ParticleManager* pm, FindKeys* keyEvent)
{
    playerManager_ = playerManager;
    pm_ = pm;
    keyEvent_ = keyEvent;
    position_ = position;
    tag_ = "Item";
    name_ = "Key";
    HP_ = 1;
    priceTag_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(32);
    arrow_ = new UIArrow(pm_, position_, HP_);

    //sprite_ = LP::SetSprite(item_heal_texture, position_);
    sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    LP::SetRectangleColor(sprite_, 100, 100, 0, 255);
}

Key::~Key()
{
    //LP::DeleteSprite(sprite_);
    LP::DeleteRectangle(sprite_);
}

void Key::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void Key::Draw(const sf::RenderWindow& render_window)
{
    LP::DrawSprite(sprite_);
}

void Key::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        LP::DrawText(text_);
    }
}

void Key::Effect()
{
    keyEvent_->PickUpKey();
}