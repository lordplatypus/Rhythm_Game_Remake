#include "BulletCasing.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"
#include "../Assets/ID.h"

BulletCasing::BulletCasing(sf::Vector2f position, bool fliped, Scene *scene, ParticleManager* pm, Map* map)
{
    position_ = position;
    int flip = 1;
    if (fliped) flip = -1;
    scene_ = scene;
    pm_ = pm;
    map_ = map;
    tag_ = "Enemy";
    name_ = "BulletCasing";
    imageWidth_ = 16;
    imageHeight_ = 24;

    SetActive(false); //turn off collision

    sprite_ = LP::SetSprite(bullet_casing_texture, position_);
    LP::SetSpriteOriginCenter(&sprite_);
    sprite_.setScale(.2f, .2f);

    lifespan_ = float(rand() % 10 + 20) / 10.0f;
    vx_ = (rand() % 30 + 10) * flip;
    vy_ = -(rand() % 50 + 20);
    damp_ = .99f;
    forceY_ = 100.0f;
    angle_ = rand() % 360 * (M_PI / 180);
    angularVelocity_ = float((rand() % 720) - 360);

    startY = position_.y;
}

BulletCasing::~BulletCasing()
{}

void BulletCasing::Update(float delta_time, float beat_time)
{
    age_ += delta_time;

    if (age_ >= lifespan_)
    {
        Kill();
        return;
    }
    else if (age_ >= lifespan_/2)
    {
        float progressRate = (age_ / (lifespan_ / 2));
        alpha_ = Math::Lerp(255, 0, progressRate);
    }  

    vx_ += forceX_ * delta_time;
    vy_ += forceY_ * delta_time;

    vx_ *= pow(damp_, delta_time*60);
    vy_ *= pow(damp_, delta_time*60);

    if (position_.y > startY) vy_ += bouncePower;

    position_.x += vx_ * delta_time;
    position_.y += vy_ * delta_time;

    angle_ += angularVelocity_ * delta_time;

    CheckMoveLocation();

    sprite_.setRotation(angle_);
    sprite_.setColor(sf::Color(255, 255, 255, alpha_));
    sprite_.setPosition(position_);
}

void BulletCasing::Draw(sf::RenderWindow& render_window) const
{
    render_window.draw(sprite_);
}

void BulletCasing::DelayedDraw(sf::RenderWindow& render_window) const
{}

void BulletCasing::ReactOnCollision(GameObject& other)
{}

void BulletCasing::ReactInRange(GameObject& other)
{}

void BulletCasing::ReactNotInRange(GameObject& other)
{}

void BulletCasing::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        vx_ = -vx_;
    }
}