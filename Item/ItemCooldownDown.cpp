#include "../Headers/ItemCooldownDown.h"
#include "../Headers/LP.h"
//#include "../Headers/Player.h"
#include "../Headers/TextureID.h"

ItemCooldownDown::ItemCooldownDown(sf::Vector2f position, int itemID, Scene *scene)
{
    scene_ = scene;
    position_ = position;
    tag_ = "Item";
    name_ = "Cooldown";
    ID_ = itemID;
    HP_ = 1;
    priceTag_ = 200;
    imageWidth_ = 32;
    imageHeight_ = 32;
    perception_ = 32;

    sprite_ = LP::SetSprite(itemSpecialCooldown, position_);

    scene_->GetUI()->AddUIArrow(position_, ID_, HP_);
    scene_->GetUI()->AddUIText(ID_, LP::SetText("CoolDown Decrease: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32));
    scene_->GetUI()->FindUIText(ID_)->SetTextScale(0.1f);
}

ItemCooldownDown::~ItemCooldownDown()
{
    LP::DeleteSprite(sprite_);
    scene_->GetUI()->RemoveUIArrow(ID_);
    scene_->GetUI()->RemoveUIText(ID_);
}

void ItemCooldownDown::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void ItemCooldownDown::Draw()
{
    LP::DrawSprite(sprite_);
}

void ItemCooldownDown::Effect()
{
    scene_->GetPlayerManager()->SetSpecialCooldown(scene_->GetPlayerManager()->GetSpecialCooldown() - 1);
    scene_->GetPlayerManager()->SubMoney(priceTag_);
    scene_->GetUI()->FindUITextCamera("Wallet")->SetText("Spare Parts: " + std::to_string(scene_->GetPlayerManager()->GetWallet()));
}