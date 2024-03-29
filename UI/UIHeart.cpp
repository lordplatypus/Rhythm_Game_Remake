#include "UIHeart.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Assets/ID.h"

UIHeart::UIHeart(Camera* camera, int numOfHearts, int heartPosition) : camera_{camera}
{
    bpm_ = MP::GetBPM(MP::GetPlayingMusic());
    heart_ = LP::SetSprite(heart_texture);
    heartSmall_ = LP::SetSprite(heart_small_texture);
    greyHeart_ = LP::SetSprite(grey_heart_texture);
    greyHeartSmall_ = LP::SetSprite(grey_heart_small_texture);
    LP::SetSpriteOriginCenter(&heart_);
    LP::SetSpriteOriginCenter(&heartSmall_);
    LP::SetSpriteOriginCenter(&greyHeart_);
    LP::SetSpriteOriginCenter(&greyHeartSmall_);
    numOfHearts_ = numOfHearts;
    heartPosition_ = heartPosition + 1;
    if (heartPosition_ != numOfHearts_)
    {
        nextHeart_ = new UIHeart(camera_, numOfHearts_, heartPosition_);
    }
}

UIHeart::~UIHeart()
{
    delete nextHeart_;
}

void UIHeart::Update(float delta_time, float beat_time)
{
    position_ = sf::Vector2f((camera_->GetCameraCenter().x - (16 * numOfHearts_) / 2) + (heartPosition_ * 16), camera_->GetCameraBottomEdge() - 32);

    if (beat_time < (bpm_ / (numOfHearts_+ 1)) * heartPosition_)
    {
        isSmall_ = true;
        heartSmall_.setPosition(position_);
        greyHeartSmall_.setPosition(position_);
    }
    else 
    {
        isSmall_ = false;
        heart_.setPosition(position_);
        greyHeart_.setPosition(position_);
    }

    if (numOfHearts_ != heartPosition_) nextHeart_->Update(delta_time, beat_time);
}

void UIHeart::Draw(sf::RenderWindow& render_window) const
{
    if (isDamaged_)
    {
        if (isSmall_) render_window.draw(greyHeartSmall_);
        else render_window.draw(greyHeart_);
    }
    else
    {
        if (isSmall_) render_window.draw(heartSmall_);
        else render_window.draw(heart_);
    }
    if (numOfHearts_ != heartPosition_) nextHeart_->Draw(render_window);
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

void UIHeart::Heal()
{
    if (isDamaged_ && !nextHeart_->IsDamaged()) 
    {
        isDamaged_ = false;
        return;
    }
    if (numOfHearts_ != heartPosition_) nextHeart_->Heal(); 
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
            nextHeart_ = new UIHeart(camera_, numOfHearts_, heartPosition_);
            nextHeart_->AddHeart(0);
        }
        else nextHeart_->AddHeart(numOfNewHearts);
    }
}

void UIHeart::RemoveHeart(int numOfHeartsToRemove)
{
    numOfHearts_ -= numOfHeartsToRemove;
    if (numOfHearts_ <= 0) numOfHearts_ = 1;
    
    if (heartPosition_ >= numOfHearts_)
    {
        if (nextHeart_ != nullptr) 
        {
            nextHeart_->RemoveHeart(numOfHeartsToRemove);
            delete nextHeart_;
            nextHeart_ = nullptr;
        }
    }
    else nextHeart_->RemoveHeart(numOfHeartsToRemove);
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

    return 0;
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

void UIHeart::SetBPM(float bpm)
{
    bpm_ = bpm;
    if (numOfHearts_ != heartPosition_) nextHeart_->SetBPM(bpm);
}