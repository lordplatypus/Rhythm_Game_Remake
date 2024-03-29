#include "UIArrow.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

UIArrow::UIArrow(ParticleManager* pm, sf::Vector2f position, int numOfArrows, int arrowPosition) : position_{position}, numOfArrows_{numOfArrows}, arrowPosition_{arrowPosition+1}
{
    pm_ = pm;
    Init();
    if (arrowPosition_ != numOfArrows_)
    {
        float x = 0.0f;
        if (arrowPosition_ != 1 && arrowPosition_ % 4 == 0) x = position_.x - 8 * 3;
        else x = position_.x + 8;
        nextArrow_ = new UIArrow(pm_, sf::Vector2f(x, position_.y), numOfArrows_, arrowPosition_);
    }
}

UIArrow::~UIArrow()
{
    delete nextArrow_;
}

void UIArrow::Init()
{
    arrowDirection_ = rand() % 4;
    if (arrowDirection_ == 0)
    {
        arrow_ = LP::SetSprite(left_arrow_texture);
        greyArrow_ = LP::SetSprite(left_arrow_grey_texture);
    }
    else if (arrowDirection_ == 1)
    {
        arrow_ = LP::SetSprite(right_arrow_texture);
        greyArrow_ = LP::SetSprite(right_arrow_grey_texture);
    }
    else if (arrowDirection_ == 2)
    {
        arrow_ = LP::SetSprite(up_arrow_texture);
        greyArrow_ = LP::SetSprite(up_arrow_grey_texture);
    }
    else
    {
        arrow_ = LP::SetSprite(down_arrow_texture);
        greyArrow_ = LP::SetSprite(down_arrow_grey_texture);
    }
}

void UIArrow::Update(float delta_time, float beat_time)
{
    HPBarManager();
}

void UIArrow::Draw(sf::RenderWindow& render_window) const
{
    if (isVisible_)
    {
        if (isDamaged_) render_window.draw(greyArrow_);
        else render_window.draw(arrow_);
    }
    if (numOfArrows_ != arrowPosition_) nextArrow_->Draw(render_window);
}

int UIArrow::GetCurrentArrow() const
{//return a num 0-3: 0 = left, 1 = right, 2 = up, 3 = down
    if (isDamaged_ && numOfArrows_ != arrowPosition_)
    {
        return nextArrow_->GetCurrentArrow();
    }
    else return arrowDirection_;
}

void UIArrow::UpdatePosition(const sf::Vector2f position)
{
    position_ = position;
    float x = 0.0f;
    if (arrowPosition_ != 1 && arrowPosition_ % 4 == 0) x = position_.x - 8 * 3;
    else x = position_.x + 8;
    arrow_.setPosition(position_);
    greyArrow_.setPosition(position_);

    if (numOfArrows_ != arrowPosition_) nextArrow_->UpdatePosition(sf::Vector2f(x, position_.y));
}

void UIArrow::TakeDamage()
{
    if (isDamaged_ && numOfArrows_ != arrowPosition_)
    {
        nextArrow_->TakeDamage();
    }
    else 
    {
        if (arrowDirection_ == 0) pm_->LeftArrowSlash(position_.x, position_.y);
        else if (arrowDirection_ == 1) pm_->RightArrowSlash(position_.x, position_.y);
        else if (arrowDirection_ == 2) pm_->UpArrowSlash(position_.x, position_.y);
        else pm_->DownArrowSlash(position_.x, position_.y);
        isDamaged_ = true;
    }
}

void UIArrow::Heal()
{
    if (!isDamaged_) return;
    else
    {
        isDamaged_ = false;
        nextArrow_->Heal();
    }
}

void UIArrow::HPBarManager(bool currentHPBar, bool nextHPBar, bool hiddenHPBar)
{
    if (arrowPosition_ % 4 == 1 && ReportNextNonDamagedArrow(0) > 3)
    {
        currentHPBar = false;
        hiddenHPBar = true;
    }

    if (currentHPBar)
    {
        arrow_.setScale(1.0f, 1.0f);
        arrow_.setColor(sf::Color(255, 255, 255, 255));
        arrow_.setOrigin(sf::Vector2f(0.0f, -2.0f));
        isVisible_ = true;
    }
    else if (nextHPBar) 
    {
        arrow_.setScale(0.5f, 0.5f);
        arrow_.setColor(sf::Color(255, 255, 255, 127));
        arrow_.setOrigin(sf::Vector2f(0.0f, -0.0f));
        isVisible_ = true;
    }
    else if (hiddenHPBar)
    {
        isVisible_ = false;
    }

    if (arrowPosition_ % 4 == 0)
    {
        if (hiddenHPBar && isDamaged_) 
        {
            currentHPBar = true;
            hiddenHPBar = false;
        }
        else if (currentHPBar) 
        {
            nextHPBar = true;
            currentHPBar = false;
        }
        else if (nextHPBar) 
        {
            hiddenHPBar = true;
            nextHPBar = false;
        }
    }

    if (numOfArrows_ != arrowPosition_) nextArrow_->HPBarManager(currentHPBar, nextHPBar, hiddenHPBar);
}

int UIArrow::ReportNextNonDamagedArrow(int arrowCount)
{
    if (!isDamaged_) return arrowCount;
    if (numOfArrows_ != arrowPosition_) return nextArrow_->ReportNextNonDamagedArrow(arrowCount+1);
    return arrowCount;//failsafe - if all arrows are damaged and this somehow gets called return a num so it doesn't crash the game
}

void UIArrow::AddArrow(int numOfArrowsToAdd)
{
    if (arrowPosition_ != numOfArrows_ + numOfArrowsToAdd)
    {
        numOfArrows_ += numOfArrowsToAdd;
        if (nextArrow_ == nullptr) //if the arrow is in the last position
        {
            nextArrow_ = new UIArrow(pm_, position_, numOfArrows_, arrowPosition_);
            nextArrow_->AddArrow(0);
        }
        else nextArrow_->AddArrow(numOfArrowsToAdd);
    }
}

void UIArrow::RemoveArrow(int numOfArrowsToRemove)
{

}