#include "Mortar.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"

Mortar::Mortar(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, ParticleManager* pm)
{
    scene_ = scene;
    lem_ = lem;
    pm_ = pm;
    position_ = position;
    tag_ = "Mortar";
    name_ = "Mortar";
    imageWidth_ = 8;
    imageHeight_ = 8;

    ed_ = lem_->Add(0, 0, 1, 0, false, 0, true);

    sprite_ = LP::SetSprite(target_texture, position_);
    sprite_.setScale(scale_, scale_);
    LP::SetSpriteOriginCenter(sprite_);

    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    SetActive(false);
}

Mortar::~Mortar()
{
}

void Mortar::Update(float delta_time, float beat_time)
{
    if (!input_ && beat_time <= windowOfInput_)
    {
        input_ = true;
        deathCount_--;
        if (deathCount_ <= 0) 
        {
            SetActive(true);
            Kill();
        }
    }
    else if (beat_time > windowOfInput_)
    {
        input_ = false;
    }

    scale_ = Math::Lerp(scale_, endingScale_, 5 * delta_time);
    sprite_.setScale(scale_, scale_);
}

void Mortar::Draw(sf::RenderWindow& render_window)
{
    render_window.draw(sprite_);
}

void Mortar::Kill()
{
    isDead_ = true;
    pm_->Explosion(position_.x, position_.y);
}

void Mortar::ReactOnCollision(GameObject& other)
{
    if (GetActive() && other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
}