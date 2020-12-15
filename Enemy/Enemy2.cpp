#include <SFML/Graphics.hpp>
#include "Enemy2.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"

Enemy2::Enemy2(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    HP_ = 4 + lem_->GetMaxHPModifier();
    position_ = position;
    tag_ = "Enemy";
    name_ = "2";
    imageWidth_ = 32;
    imageHeight_ = 32;
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);

    ed_ = lem_->Add(HP_, HP_, 1, 0, true, 1, false);

    enemy2Rect_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    LP::SetRectangleColor(enemy2Rect_, 0, 0, 255, 255);

    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Enemy2::~Enemy2()
{}

void Enemy2::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (!hasMoved_)
        {
            beatCount_++;
            StorePosition();
        }
        if (beatCount_ == 2)
        {
            beatCount_ = 0;
            if (movedDown_) 
            {
                position_.y -= CellSize;
                movedDown_ = false;
            }
            else 
            {
                position_.y += CellSize;
                movedDown_ = true;
            }
            CheckMoveLocation();
        }
        hasMoved_ = true;
    }
    else if (delayAttack_)
    {
        StorePosition();
        if (movedDown_ == true) movedDown_ = false;
        else movedDown_ = true;
        
        if (movedDown_) 
        {
            position_.y -= CellSize;
            movedDown_ = false;
        }
        else 
        {
            position_.y += CellSize;
            movedDown_ = true;
        }
        delayAttack_ = false;
    }
    else hasMoved_ = false;

    velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(velocity_);
}

void Enemy2::Draw()
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) LP::DrawRectangle(enemy2Rect_, velocity_);
}

void Enemy2::DelayedDraw()
{
    if (GetInRangeOfPlayer()) arrow_->Draw();
}

void Enemy2::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        position_ = GetPrevPosition();
    }

    if (position_ == scene_->FindGameObject("Player")->GetPosition())
    {
        position_ = GetPrevPosition();
        delayAttack_ = true;
    }
}

void Enemy2::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition") return;
    if (other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
    position_ = GetPrevPosition();
    if (movedDown_) movedDown_ = false;
    else movedDown_ = true;
    beatCount_ = 1;
}