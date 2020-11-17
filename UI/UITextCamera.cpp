#include "../Headers/UITextCamera.h"
#include "../Headers/LP.h"
#include "../Headers/Math.h"

UITextCamera::UITextCamera(const int textKey, const std::string& name, sf::Vector2f position, Camera* camera)
{
    textKey_ = textKey;
    tag_ = "TextCamera";
    name_ = name;
    camera_ = camera;
    position_ = position;
    SetTextPosition(sf::Vector2f(camera_->GetCameraLeftEdge() + position_.x, camera_->GetCameraTopEdge() + position_.y));
}

UITextCamera::~UITextCamera()
{
    LP::DeleteText(ID_);
}

void UITextCamera::Init()
{}

void UITextCamera::Update(float delta_time, float beat_time)
{
    SetTextPosition(sf::Vector2f(camera_->GetCameraLeftEdge() + position_.x, camera_->GetCameraTopEdge() + position_.y));
}

void UITextCamera::Draw() const
{
    if (isVisible_) LP::DrawText(textKey_);
}

void UITextCamera::SetText(const std::string& text)
{
    LP::SetTextString(textKey_, text);
}

void UITextCamera::SetTextPosition(const sf::Vector2f position)
{
    LP::SetTextPosition(textKey_, position);
}

void UITextCamera::SetTextColor(const int red, const int green, const int blue, const int alpha)
{
    LP::SetTextColor(textKey_, red, green, blue, alpha);
}

void UITextCamera::SetTextSize(const int textSize)
{}

void UITextCamera::SetTextScale(const float textScale)
{
    LP::SetTextScale(textKey_, textScale, textScale);
}

void UITextCamera::SetTextVisiblity(const bool isVisible)
{
    isVisible_ = isVisible;
}

void UITextCamera::SetTextOrigin(const sf::Vector2f origin)
{
    LP::SetTextOrigin(textKey_, origin);
}

void UITextCamera::SetTextOriginCenter()
{
    LP::SetTextOriginCenter(textKey_);
}