#include <SFML/Graphics.hpp>
#include "Enemy1.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Assets/ID.h"
using namespace std;
using namespace sf;

Enemy1::Enemy1(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    HP_ = 4 + lem_->GetMaxHPModifier();
    tag_ = "Enemy";
    name_ = "1";
    imageWidth_ = 32;
    imageHeight_ = 32;
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);

    ed_ = lem_->Add(HP_, HP_, 1, 0, true, 1);

    enemySprite_ = LP::SetSprite(companion_texture, 32, 32, 8, 1);
    for (auto i : enemySprite_)
    {
        LP::SetSpriteOrigin(i, Vector2f(6,6));
    }
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 8.0f;

    arrow_ = new UIArrow(pm_, position_, HP_);
    //arrow_->UpdateVisiblity(true);
}

Enemy1::~Enemy1()
{
    for (auto i : enemySprite_)
    {
        LP::DeleteSprite(i);
    }
}

void Enemy1::Update(float delta_time, float beat_time)
{
    AnimationHandle(delta_time, beat_time);
    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(position_);
}

void Enemy1::Draw()
{
    LP::DrawSprite(enemySprite_[animCount_], position_);
}

void Enemy1::DelayedDraw()
{
    if (GetInRangeOfPlayer()) arrow_->Draw();
}

void Enemy1::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition") return;
    if (other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
}

void Enemy1::AnimationHandle(float delta_time, float beat_time)
{   
    timer_ += delta_time;
    if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
    else if (animCount_ != 7 && timer_ >= timeInbetweenFrames_) 
    {
        animCount_++;
        timer_ = 0;
    }
}