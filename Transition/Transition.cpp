#include "Transition.h"

Transition::Transition(TransitionManager* tm, const std::string& transitionTo, const sf::Vector2f position, const bool locked, Scene* scene, ParticleManager* particleManager) :
    tm_{tm}, particleManager_{particleManager}
{
    scene_ = scene;
    position_ = position;
    tag_ = "Transition";
    name_ = transitionTo;
    imageWidth_ = 32;
    imageHeight_ = 32;

    tm_->Add(name_, locked);

    // if (name_ == "JunkYard")
    // {
    //     sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    //     LP::SetRectangleColor(sprite_, 255, 0, 255, 255);
    // }
}

Transition::~Transition()
{}

void Transition::Update(float delta_time, float beat_time)
{
    if (foundPlayer_) 
    {
        count_ -= delta_time;

        if (count_ <= 0) 
        {
            scene_->ChangeScene(name_);
            count_ = 1.0f;
            foundPlayer_ = false;
            Kill();
        }
    }
}

void Transition::Draw()
{
    //if (name_ == "JunkYard") LP::DrawRectangle(sprite_);
}

void Transition::ReactOnCollision(GameObject& other)
{
    if (tm_->IsLocked(name_)) return; 
    if (other.GetTag() == "Player")
    {
        if (!foundPlayer_) particleManager_->FadeToBlack(scene_->FindGameObject("Player", true)->GetPosition().x, scene_->FindGameObject("Player", true)->GetPosition().y);
        foundPlayer_ = true;
    }
}