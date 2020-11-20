#include "../Headers/ItemAddHeart.h"
#include "../Headers/LP.h"
//#include "../Headers/Player.h"
#include "../Headers/TextureID.h"

ItemAddHeart::ItemAddHeart(sf::Vector2f position, int itemID, Scene *scene)
{
    scene_ = scene;
    position_ = position;
    tag_ = "Item";
    name_ = "MaxHP";
    ID_ = itemID;
    HP_ = 1;
    priceTag_ = 69;
    imageWidth_ = 32;
    imageHeight_ = 32;
    perception_ = 32;

    sprite_ = LP::SetSprite(itemMaxHP, position_);

    scene_->GetUI()->AddUIArrow(position_, ID_, HP_);
    scene_->GetUI()->AddUIText(ID_, LP::SetText("Max HP Up: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32));
    scene_->GetUI()->FindUIText(ID_)->SetTextScale(0.1f);
}

ItemAddHeart::~ItemAddHeart()
{
    LP::DeleteSprite(sprite_);
    scene_->GetUI()->RemoveUIArrow(ID_);
    scene_->GetUI()->RemoveUIText(ID_);
}

void ItemAddHeart::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void ItemAddHeart::Draw()
{
    LP::DrawSprite(sprite_);
}

void ItemAddHeart::Effect()
{
    scene_->GetPlayerManager()->SetMaxHP(scene_->GetPlayerManager()->GetMaxHP() + 1);
    scene_->GetUI()->FindUIHeart(scene_->FindGameObject("Player")->GetID())->AddHeart(1);
    scene_->GetUI()->FindUIHeart(scene_->FindGameObject("Player")->GetID())->TakeDamage(1);
    scene_->GetPlayerManager()->SubMoney(priceTag_);
    scene_->GetUI()->FindUITextCamera("Wallet")->SetText("Spare Parts: " + std::to_string(scene_->GetPlayerManager()->GetWallet()));
}