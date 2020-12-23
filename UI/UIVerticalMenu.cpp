#include "UIVerticalMenu.h"
#include "../Engine/LP.h"
#include "../Engine/Math.h"

UIVerticalMenu::UIVerticalMenu(sf::Vector2f position, int numOfText, std::vector<sf::Text> textArray, int numToDisplay, int numAboveSelected, int textSpacing, int textPosition)
{
    text_ = textArray[textPosition];
    menuPosition_ = textPosition;
    textPosition_ = textPosition + 1;
    numToDisplay_ = numToDisplay;
    numAboveSelected_ = numAboveSelected;
    textSpacing_ = textSpacing;
    staticPosition_ = position;
    position_ = staticPosition_;
    if (menuPosition_ == numOfText_ - 1) position_.y = staticPosition_.y - 64;
    else position_.y = staticPosition_.y + menuPosition_ * 64;
    text_.setPosition(position_);
    endPosition_ = position_;
    numOfText_ = numOfText;
    if (menuPosition_ != 0) 
    {
        alpha_ = 255/4;
        text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    }

    if (textPosition_ != numOfText_)
    {
        nextText_ = new UIVerticalMenu(staticPosition_, numOfText_, textArray, numToDisplay_, numAboveSelected_, textSpacing_, textPosition_);
    }
}

UIVerticalMenu::~UIVerticalMenu()
{
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
        text_.setPosition(position_);
    }
}

void UIVerticalMenu::Draw(sf::RenderWindow& render_window) const
{
    if (display_ == false) return;

    if (menuPosition_ >= numOfText_ - numAboveSelected_) render_window.draw(text_);
    if (menuPosition_ <= numToDisplay_ - 1 - numAboveSelected_) render_window.draw(text_);

    if (numOfText_ != textPosition_) nextText_->Draw(render_window);
}

void UIVerticalMenu::ScrollUp()
{
    menuPosition_++;
    if (menuPosition_ > numOfText_ - 1) menuPosition_ = 0; 
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    if (numOfText_ != textPosition_) nextText_->ScrollUp();
}

void UIVerticalMenu::ScrollDown()
{
    menuPosition_--;
    if (menuPosition_ < 0) menuPosition_ = numOfText_ - 1;
    if (menuPosition_ == 0) alpha_ = 255;
    else alpha_ = 255/4;
    text_.setFillColor(sf::Color(255, 255, 255, alpha_));
    if (numOfText_ != textPosition_) nextText_->ScrollDown();
}

void UIVerticalMenu::SetDisplay(const bool display)
{
    display_ = display;
}