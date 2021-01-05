#include "Item.h"

Item::Item()
{}

Item::~Item()
{
    delete arrow_;
}

void Item::Update(float delta_time, float beat_time)
{
    SparkleRandom(delta_time);
}

void Item::Draw(sf::RenderWindow& render_window)
{
    render_window.draw(sprite_);
}

void Item::DelayedDraw(sf::RenderWindow& render_window)
{
    if (ifSeesPlayer_) 
    {
        arrow_->Draw(render_window);
        render_window.draw(text_);
    }
}

int Item::GetPriceTag() const
{
    return priceTag_;
}

void Item::SparkleRandom(float delta_time)
{
    sparkleTime -= delta_time;
    if (sparkleTime <= 0)
    {
        sparkleTime = (float)(rand() % 3 + 1) / (float)(rand() % 5 + 1);
        Sparkle();
    }
}

void Item::Kill()
{
    isDead_ = true;
    //delete arrow_;
}

void Item::TakeDamage(const int damage)
{
    if (!ifSeesPlayer_ || damage == -1) return;
    if (playerManager_->GetWallet() < priceTag_) return;
    if (damage == arrow_->GetCurrentArrow())
    {
        arrow_->TakeDamage();
        Effect();
        Kill();
    }
}

void Item::ReactInRange(GameObject& other)
{
    if (other.GetTag() == "Player")
    {
        ifSeesPlayer_ = true;
        //arrow_->UpdateVisiblity(true);
        //scene_->GetUI()->FindUIText(ID_)->SetTextVisiblity(isInRange);
    }
}

void Item::ReactNotInRange(GameObject& other)
{
    if (other.GetTag() == "Player")
    {
        ifSeesPlayer_ = false;
        //arrow_->UpdateVisiblity(false);
    }
}

void Item::Sparkle()
{
    int sparkleX = position_.x + (rand() % 32);
    int sparkleY = position_.y + (rand() % 32);
    pm_->Sparkle(sparkleX, sparkleY);
}