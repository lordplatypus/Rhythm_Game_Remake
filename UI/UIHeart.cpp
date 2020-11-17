#include "UIHeart.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

UIHeart::UIHeart(Camera* camera, int numOfHearts, float bpm, int heartPosition) : camera_{camera}
{
    bpm_ = bpm;
    heart_ = LP::SetSprite(heart_texture);
    heartSmall_ = LP::SetSprite(heart_small_texture);
    greyHeart_ = LP::SetSprite(grey_heart_texture);
    greyHeartSmall_ = LP::SetSprite(grey_heart_small_texture);
    LP::SetSpriteOrigin(heart_, sf::Vector2f(8, 8));
    LP::SetSpriteOrigin(heartSmall_, sf::Vector2f(8, 8));
    LP::SetSpriteOrigin(greyHeart_, sf::Vector2f(8, 8));
    LP::SetSpriteOrigin(greyHeartSmall_, sf::Vector2f(8, 8));
    numOfHearts_ = numOfHearts;
    heartPosition_ = heartPosition + 1;
    if (heartPosition_ != numOfHearts_)
    {
        nextHeart_ = new UIHeart(camera_, numOfHearts_, bpm_,  heartPosition_);
    }
}

UIHeart::~UIHeart()
{
    LP::DeleteSprite(heart_);
    LP::DeleteSprite(heartSmall_);
    LP::DeleteSprite(greyHeart_);
    LP::DeleteSprite(greyHeartSmall_);
    delete nextHeart_;
}

void UIHeart::Update(float delta_time, float beat_time)
{
    position_ = sf::Vector2f((camera_->GetCameraCenter().x - (16 * numOfHearts_) / 2) + (heartPosition_ * 16), camera_->GetCameraBottomEdge() - 32);

    if (beat_time < (bpm_ / (numOfHearts_+ 1)) * heartPosition_)
    {
        isSmall_ = true;
    }
    else isSmall_ = false;

    if (numOfHearts_ != heartPosition_) nextHeart_->Update(delta_time, beat_time);
}

void UIHeart::Draw() const
{
    if (isDamaged_)
    {
        if (isSmall_) LP::DrawSprite(greyHeartSmall_, position_);
        else LP::DrawSprite(greyHeart_, position_);
    }
    else
    {
        if (isSmall_) LP::DrawSprite(heartSmall_, position_);
        else LP::DrawSprite(heart_, position_);
    }
    if (numOfHearts_ != heartPosition_) nextHeart_->Draw();
}

bool UIHeart::IsDamaged()
{
    return isDamaged_;
}

void UIHeart::TakeDamage(int amountOfDamage)
{
    if (!isDamaged_)
    {
        isDamaged_ = true;
        amountOfDamage--;
    }
    if (amountOfDamage > 0 && numOfHearts_ != heartPosition_)
    {
        nextHeart_->TakeDamage(amountOfDamage);
    }
}

void UIHeart::Heal(int amountToHeal)
{
    if (isDamaged_ && !nextHeart_->IsDamaged()) 
    {
        isDamaged_ = false;
        amountToHeal--;
    }
    if (amountToHeal > 0 && numOfHearts_ != heartPosition_) nextHeart_->Heal(amountToHeal); 
}

void UIHeart::AddHeart(int numOfNewHearts)
{
    if (heartPosition_ != numOfHearts_ + numOfNewHearts)
    {
        numOfHearts_ += numOfNewHearts;
        if (nextHeart_ == nullptr) //if the heart is in the last position
        {
            nextHeart_ = new UIHeart(camera_, numOfHearts_, bpm_, heartPosition_);
            nextHeart_->AddHeart(0);
        }
        else nextHeart_->AddHeart(numOfNewHearts);
    }
}

void UIHeart::RemoveHeart(int numOfHeartsToRemove)
{
    
}

int UIHeart::GetNumOfHeart() const
{
    return numOfHearts_;
}

void UIHeart::SetNumOfHeart(const int numOfHeart)
{
    if (numOfHearts_ == numOfHeart) return;
    else if (numOfHearts_ < numOfHeart)
    {
        AddHeart(numOfHeart - numOfHearts_);
    }
    else if (numOfHearts_ > numOfHeart)
    {
        RemoveHeart(numOfHearts_ - numOfHeart);
    }
}

int UIHeart::GetDamage(int count) const
{
    if (isDamaged_) count++;
    else return count;
    if (numOfHearts_ != heartPosition_) nextHeart_->GetDamage(count);
}

void UIHeart::SetDamage(const int damage)
{
    if (GetDamage() == damage) return;
    else if (GetDamage() < damage)
    {
        TakeDamage(damage - GetDamage());
    }
    else if (GetDamage() > damage)
    {
        Heal(GetDamage() - damage);
    }
}