#include "../Headers/ItemPerceptionUp.h"
#include "../Headers/LP.h"
#include "../Headers/TextureID.h"

ItemPerceptionUp::ItemPerceptionUp(sf::Vector2f position, int itemID, Scene *scene)
{
    scene_ = scene;
    position_ = position;
    tag_ = "Item";
    ID_ = itemID;
    HP_ = 1;
    priceTag_ = 200;
    imageWidth_ = 32;
    imageHeight_ = 32;
    perception_ = 32;

    sprite_ = LP::SetSprite(itemRange, position_);

    scene_->GetUI()->AddUIArrow(position_, ID_, HP_);
    scene_->GetUI()->AddUIText(ID_, LP::SetText("Range Up: " + std::to_string(priceTag_), sf::Vector2f(position_.x, position_.y - 4), 32));
    scene_->GetUI()->FindUIText(ID_)->SetTextScale(0.1f);
}

ItemPerceptionUp::~ItemPerceptionUp()
{
    LP::DeleteSprite(sprite_);
    scene_->GetUI()->RemoveUIArrow(ID_);
    scene_->GetUI()->RemoveUIText(ID_);
}

void ItemPerceptionUp::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void ItemPerceptionUp::Draw()
{
    LP::DrawSprite(sprite_);
}

void ItemPerceptionUp::Effect()
{
    scene_->GetPlayerManager()->SetRange(scene_->GetPlayerManager()->GetRange() + CellSize);
    scene_->GetPlayerManager()->SubMoney(priceTag_);
    scene_->GetUI()->FindUITextCamera("Wallet")->SetText("Spare Parts: " + std::to_string(scene_->GetPlayerManager()->GetWallet()));
}