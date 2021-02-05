#include <SFML/Graphics.hpp>
#include "Enemy2.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"
#include "../Assets/ID.h"

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

    ed_ = lem_->Add(HP_, HP_, 1, 0, true, 1, false);

    enemySprite_ = LP::SetMultiFrameSprite(minecart_texture, 32, 32, 5, 4);
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 8.0f;

    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);

    //rails_.push_back(LP::SetSprite(rail_texture, position_));
    //if (!map_->IsWall(position_ + sf::Vector2f(0.0f, 32.0f))) rails_.push_back(LP::SetSprite(rail_texture, position_ + sf::Vector2f(0.0f, 32.0f)));
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

    AnimationHandle(delta_time, beat_time);

    velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(velocity_);
    enemySprite_[animCount_].setPosition(velocity_);
}

void Enemy2::Draw(sf::RenderWindow& render_window) const
{
    //if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) LP::DrawRectangle(enemy2Rect_, velocity_);
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer())
    {
        for(auto i : rails_) render_window.draw(i);
        render_window.draw(enemySprite_[animCount_]);
    } 
}

void Enemy2::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (GetInRangeOfPlayer()) arrow_->Draw(render_window);
}

void Enemy2::AnimationHandle(float delta_time, float beat_time)
{   
    timer_ += delta_time;
    if (movedDown_)
    {
        if (beatCount_ == 1)
        {
            if (beat_time <= timeInbetweenFrames_) animCount_ = 5;     
            else if (animCount_ != 9 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
        else
        {
            if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
            else if (animCount_ != 4 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
    }
    else
    {
        if (beatCount_ == 1)
        {
            if (beat_time <= timeInbetweenFrames_) animCount_ = 15;     
            else if (animCount_ != 19 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
        else
        {
            if (beat_time <= timeInbetweenFrames_) animCount_ = 10;     
            else if (animCount_ != 14 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
    }
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