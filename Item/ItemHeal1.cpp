#include "../Headers/ItemHeal1.h"
#include "../Headers/LP.h"
//#include "../Headers/Player.h"
#include "../Headers/TextureID.h"

ItemHeal1::ItemHeal1(sf::Vector2f position, int itemID, Scene *scene)
{
    scene_ = scene;
    position_ = position;
    tag_ = "Item";
    name_ = "Heal";
    ID_ = itemID;
    HP_ = 1;
    priceTag_ = 100;
    imageWidth_ = 32;
    imageHeight_ = 32;
    perception_ = 32;

    // sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    // LP::SetRectangleColor(sprite_, 255, 255, 0, 255);

    sprite_ = LP::SetSprite(itemHeal, position_);

    scene_->GetUI()->AddUIArrow(position_, ID_, HP_);
    scene_->GetUI()->AddUIText(ID_, LP::SetText("Heal 1: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32));
    scene_->GetUI()->FindUIText(ID_)->SetTextScale(0.1f);
}

ItemHeal1::~ItemHeal1()
{
    //LP::DeleteRectangle(sprite_);
    LP::DeleteSprite(sprite_);
    scene_->GetUI()->RemoveUIArrow(ID_);
    scene_->GetUI()->RemoveUIText(ID_);
}

void ItemHeal1::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void ItemHeal1::Draw()
{
    //LP::DrawRectangle(sprite_);
    LP::DrawSprite(sprite_);
}

void ItemHeal1::Effect()
{
    scene_->GetUI()->FindUIHeart(scene_->FindGameObject("Player")->GetID())->Heal(1);
    scene_->GetPlayerManager()->AddHP(1);
    scene_->GetPlayerManager()->SubMoney(priceTag_);
    scene_->GetUI()->FindUITextCamera("Wallet")->SetText("Spare Parts: " + std::to_string(scene_->GetPlayerManager()->GetWallet()));
}