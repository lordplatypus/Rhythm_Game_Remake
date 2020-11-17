#include "../Headers/UIText.h"
#include "../Headers/LP.h"
#include "../Headers/Math.h"


UIText::UIText(const int textKey, const int ID)
{
    textKey_ = textKey;
    ID_ = ID;
    tag_ = "Text";
}

UIText::~UIText()
{
    LP::DeleteText(ID_);
}

void UIText::Init()
{}

void UIText::Update(float delta_time, float beat_time)
{}

void UIText::Draw() const
{
    if (isVisible_) LP::DrawText(textKey_);
}

void UIText::SetText(const std::string& text)
{
    LP::SetTextString(textKey_, text);
}

void UIText::SetTextPosition(const sf::Vector2f position)
{
    LP::SetTextPosition(textKey_, position);
}

void UIText::SetTextColor(const int red, const int green, const int blue, const int alpha)
{
    LP::SetTextColor(textKey_, red, green, blue, alpha);
}

void UIText::SetTextSize(const int textSize)
{}

void UIText::SetTextScale(const float textScale)
{
    LP::SetTextScale(textKey_, textScale, textScale);
}

void UIText::SetTextVisiblity(const bool isVisible)
{
    isVisible_ = isVisible;
}