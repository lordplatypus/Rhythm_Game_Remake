#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::Update(float delta_time, float beat_time)
{}

void GameObject::DelayedUpdate(float delta_time, float beat_time)
{}

void GameObject::Draw(sf::RenderWindow& render_window) const
{}

void GameObject::DelayedDraw(sf::RenderWindow& render_window) const
{}

void GameObject::ReactOnCollision(GameObject& other)
{}

void GameObject::ReactOnMissedCollision(GameObject& other)
{}

void GameObject::ReactInRange(GameObject& other)
{}

void GameObject::ReactNotInRange(GameObject& other)
{}

void GameObject::StorePosition()
{
    prevPosition_ = position_;
}

sf::IntRect GameObject::GetHitBox() const
{
    return sf::IntRect(position_.x, position_.y, imageWidth_, imageHeight_);
}

sf::IntRect GameObject::GetPerceptionHitBox() const
{
    return sf::IntRect(position_.x - GetPerception(), position_.y - GetPerception(), imageWidth_ + GetPerception()*2, imageHeight_ + GetPerception()*2);
}

bool GameObject::IsCollision(GameObject& other)
{
    return GetHitBox().intersects(other.GetHitBox());
}

void GameObject::OnCollision(GameObject& other)
{
    ReactOnCollision(other);
    other.ReactOnCollision(*this);
}

void GameObject::OnMissedCollision(GameObject& other)
{
    ReactOnMissedCollision(other);
    other.ReactOnMissedCollision(*this);
}

void GameObject::OnOneWayCollision(GameObject& other)
{
    ReactOnCollision(other);
}

void GameObject::OnMissedOneWayCollision(GameObject& other)
{
    ReactOnMissedCollision(other);
}

bool GameObject::Perception(GameObject& other)
{
    return GetPerceptionHitBox().intersects(other.GetHitBox());
}

void GameObject::InRange(GameObject& other)
{
    ReactInRange(other);
}

void GameObject::NotInRange(GameObject& other)
{
    ReactNotInRange(other);
}

void GameObject::SetPerception(const float perception)
{
    perception_ = perception;
}

float GameObject::GetPerception() const
{
    return perception_;
}

void GameObject::SetInRangeOfPlayer(const bool inRangeOfPlayer)
{}

bool GameObject::GetInRangeOfPlayer() const
{
    return false;
}

bool GameObject::GetActive() const
{
    return isActive_;
}

void GameObject::SetActive(const bool isActive)
{
    isActive_ = isActive;
}

void GameObject::TakeDamage(const int damage)
{}

void GameObject::Kill()
{
    isDead_ = true;
}

//SPRITE
void GameObject::SetSpriteHorizontalFlip(sf::Sprite& sprite, const bool flip)
{
    if (flip && sprite.getScale().x > 0)
    {
        sprite.scale(-1.0f, 1.0f);
        sprite.setOrigin(sprite.getLocalBounds().width, sprite.getOrigin().y);
    }
    else if (!flip && sprite.getScale().x < 0)
    {
        sprite.scale(-1.0f, 1.0f);
        sprite.setOrigin(0, sprite.getOrigin().y);
    }
}

void GameObject::SetSpriteOriginCenter(sf::Sprite& sprite)
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}


sf::Vector2f GameObject::GetPosition() const
{
    return position_;
}

sf::Vector2f GameObject::GetPrevPosition() const
{
    return prevPosition_;
}

bool GameObject::IsDead() const
{
    return isDead_;
}

const std::string& GameObject::GetTag() const
{
    return tag_;
}

const std::string& GameObject::GetName() const
{
    return name_;
}

int GameObject::GetID() const
{
    return ID_;
}