#include "Event.h"
#include "../Engine/LP.h"

Event::Event()
{}

Event::~Event()
{
    End();
}

void Event::DelayedDraw(sf::RenderWindow& render_window)
{
    render_window.draw(instructionText_);
}

void Event::Lock()
{
    transitionManager_->Lock(target_);
}

void Event::Unlock()
{
    transitionManager_->Unlock(target_);
}

void Event::SetInstructionText(const std::string& text)
{
    string_ = text;
}

void Event::SetInstructionTextString(const std::string& text)
{
    instructionText_.setString(text);
}

void Event::DisplayInstructionsText(float delta_time)
{
    if (state_ == Display_) 
    {
        Display();
    }
    else if (state_ == Type_)
    {
        timer_ -= delta_time;
        Type();
    }
    else if (state_ == Fadeout_)
    {
        timer_ -= delta_time;
        Fadeout();
    }
    else if (state_ == Setup_)
    {
        Setup();
    }
}

void Event::Setup()
{
    instructionText_ = LP::SetText("", camera_->GetCameraCenter(), 32, sf::Vector2f(0.3f, 0.3f));
    LP::SetTextOriginCenter(&instructionText_);
    state_ = Type_;
}

void Event::Type()
{
    instructionText_.setPosition(sf::Vector2f(camera_->GetCameraCenter().x, camera_->GetCameraCenter().y - 32));
    if (timer_ <= 0.0f)
    {
        timer_ = 0.1f;
        displayString_ += string_[count_];
        count_++;
        if (count_ == string_.size()) state_ = Fadeout_;
        instructionText_.setString(displayString_);
        LP::SetTextOriginCenter(&instructionText_);
    }
}

void Event::Fadeout()
{
    instructionText_.setPosition(sf::Vector2f(camera_->GetCameraCenter().x, camera_->GetCameraCenter().y - 32));
    if (timer_ <= 0.0f)
    {
        timer_ = 0.1f;
        alpha_ -= 10;
        instructionText_.setFillColor(sf::Color(255, 255, 255, alpha_));
        if (alpha_ <= 0) 
        {
            state_ = Display_;
            instructionText_.setScale(0.1f, 0.1f);
            instructionText_.setOrigin(sf::Vector2f(0.0f, 0.0f));
        }
    }
}

void Event::Display()
{
    instructionText_.setPosition(sf::Vector2f(camera_->GetCameraLeftEdge() + 32, camera_->GetCameraTopEdge() + 32));
}

void Event::End()
{
}

void Event::EventTrigger()
{}