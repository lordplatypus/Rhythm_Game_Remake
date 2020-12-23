#include "UIVerticalMenu.h"
#include "../Engine/LP.h"
#include "../Engine/Math.h"

UIVerticalMenu::UIVerticalMenu(sf::Vector2f position, int numOfText, std::vector<int> textIDs, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition)
{
    textKey_ = textIDs[textPosition];
    menuPosition_ = textPosition;
    textPosition_ = textPosition + 1;
    numToDisplay_ = numToDisplay;
    numAboveSelected_ = numAboveSelected;
    textSpacing_ = textSpacing;
    staticPosition_ = position;
    position_ = staticPosition_;
    if (menuPosition_ == numOfText_ - 1) position_.y = staticPosition_.y - 64;
    else position_.y = staticPosition_.y + menuPosition_ * 64;
    LP::SetTextPosition(textKey_, position_);
    endPosition_ = position_;
    numOfText_ = numOfText;
    if (menuPosition_ != 0) 
    {
        alpha_ = 255/4;
        LP::SetTextColor(textKey_, 255, 255, 255, alpha_);
    }

    if (textPosition_ != numOfText_)
    {
        nextText_ = new UIVerticalMenu(staticPosition_, numOfText_, textIDs, numToDisplay_, numAboveSelected_, textSpacing_, textPosition_);
    }
}

UIVerticalMenu::~UIVerticalMenu()
{
    LP::DeleteText(textKey_);
    delete nextText_;
}

void UIVerticalMenu::Update(float delta_time, float beat_time)
{
    if (menuPosition_ >= numToDisplay_) endPosition_.y = staticPosition_.y + (menuPosition_ - numOfText_) * textSpacing_;
    else endPosition_.y = staticPosition_.y + menuPosition_ * textSpacing_;
    if (numOfText_ != textPosition_) nextText_->Update(delta_time, beat_time);

    if (position_ != endPosition_)
    {
        position_ = Math::Lerp(position_, endPosition_, 10 * delta_time);
        LP::SetTextPosition(textKey_, position_);
    }
    
}

void UIVerticalMenu::Draw(const sf::RenderWindow& render_window) const
{
    if (display_ == false) return;

    if (menuPosition_ >= numOfText_ - numAboveSelected_) LP::DrawText(textKey_);
    if (menuPosition_ <= numToDisplay_ - 1 - numAboveSelected_) LP::DrawText(textKey_);

    if (numOfText_ != textPosition_) nextText_->Draw(render_window);
}

void UIVerticalMenu::ScrollUp()
{
    menuPosition_++;
    if (menuPosition_ > numOfText_ - 1) menuPosition_ = 0; 
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    LP::SetTextColor(textKey_, 255, 255, 255, alpha_);
    if (numOfText_ != textPosition_) nextText_->ScrollUp();
}

void UIVerticalMenu::ScrollDown()
{
    menuPosition_--;
    if (menuPosition_ < 0) menuPosition_ = numOfText_ - 1;
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    LP::SetTextColor(textKey_, 255, 255, 255, alpha_);
    if (numOfText_ != textPosition_) nextText_->ScrollDown();
}

void UIVerticalMenu::SetDisplay(const bool display)
{
    display_ = display;
}