#include "TutorialTextObject.h"
#include "../Engine/LP.h"

TutorialTextObject::TutorialTextObject(sf::Vector2f position, const std::string& text, Scene *scene)
{
    position_ = position;
    scene_ = scene;
    tag_ = "Text";
    name_ = "Info";
    imageWidth_ = 32;
    imageHeight_ = 32;
    SetPerception(96);

    text_ = LP::SetText(text, position_ + sf::Vector2f(16.0f, -64.0f), 32, sf::Vector2f(0.1f, 0.1f));
    LP::SetTextOriginCenter(&text_);
}

TutorialTextObject::~TutorialTextObject()
{}

void TutorialTextObject::Update(float delta_time, float beat_time)
{}

void TutorialTextObject::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (displayText_) render_window.draw(text_);
}

void TutorialTextObject::ReactInRange(GameObject& other)
{
    if (other.GetTag() == "Player") 
    {
        displayText_ = true;
    }
}

void TutorialTextObject::ReactNotInRange(GameObject& other)
{
    if (other.GetTag() == "Player") 
    {
        displayText_ = false;
    }
}