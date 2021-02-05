#include <SFML/Graphics.hpp>
#include "Enemy5.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Assets/ID.h"
#include "../Engine/Math.h"
#include "../Item/Money.h"
#include "../Enemy/Enemy6.h"

Enemy5::Enemy5(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    HP_ = 5 + lem_->GetMaxHPModifier();
    position_ = position;
    tag_ = "Enemy";
    name_ = "5";
    imageWidth_ = 32;
    imageHeight_ = 32;
    numOfBeatsBetweenAttacks_ = 3;
    beatCount_ = 2;
    animCount_ = 6;
    flip_ = false;

    ed_ = lem_->Add(HP_, HP_, 1, 0, true, 1, false);

    enemySprite_ = LP::SetMultiFrameSprite(tower_texture, 32, 64, 8, 1);
    for (int i = 0; i < enemySprite_.size(); i++) enemySprite_[i].setOrigin(sf::Vector2f(0.0f, 32.0f));

    StorePosition();
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 8.0f;
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Enemy5::~Enemy5()
{
}

void Enemy5::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (state_ == Angry && !hasMoved_) 
        {
            if (beatCount_ < numOfBeatsBetweenAttacks_) beatCount_++;
            else
            {
                beatCount_ = 0;
                if (!scene_->FindGameObject("Player")->IsDead()) SpawnPawn();
                pm_->SmokeScreen(position_.x + 16, position_.y + 16);
            }
        }
        hasMoved_ = true;
    }
    else hasMoved_ = false;

    AnimationHandle(delta_time, beat_time);
    enemySprite_[animCount_].setPosition(position_);

    //velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(position_);
}

void Enemy5::Draw(sf::RenderWindow& render_window) const
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) render_window.draw(enemySprite_[animCount_]);
}

void Enemy5::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (GetInRangeOfPlayer()) arrow_->Draw(render_window);
}

void Enemy5::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition") return;
    if (other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
}

void Enemy5::TakeDamage(const int damage)
{
    if (damage == -1) return;
    if (damage == arrow_->GetCurrentArrow())
    {
        state_ = Angry;
        for (int i = 0; i < playerManager_->GetAtk(); i++)
        {
            arrow_->TakeDamage();
            ed_->hp_--;
        }
        if (ed_->hp_ <= 0)
        {
            pm_->EnemyDeath(position_.x+imageWidth_/2, position_.y+imageHeight_/2);
            DropMoney();
            Kill();
        }
    }
    else if (ed_->heal_ && lem_->GetHealModifier())
    {
        ed_->hp_ = ed_->maxhp_ + lem_->GetMaxHPModifier();
        arrow_->Heal();
    }
}

void Enemy5::AnimationHandle(float delta_time, float beat_time)
{
    timer_ += delta_time;
    if (beatCount_ == 3)
    {
        animCount_ = 7;
    }
    else if (beatCount_ == 2)
    {
        if (beat_time <= timeInbetweenFrames_) animCount_ = 4;     
        else if (animCount_ != 6 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (beatCount_ == 1)
    {
        if (beat_time <= timeInbetweenFrames_) animCount_ = 1;     
        else if (animCount_ != 3 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (beatCount_ == 0)
    {
        animCount_ = 0;
    }
}

void Enemy5::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        position_ = GetPrevPosition();
    }
}

void Enemy5::SpawnPawn()
{
    sf::Vector2f pawnPosition;
    //srand(time(NULL));
    do
    {
        int teleportLocation = (rand() % 4);
        switch (teleportLocation)
        {
        case 0:
            pawnPosition.x = position_.x - CellSize;
            pawnPosition.y = position_.y;
            break;
        case 1:
            pawnPosition.x = position_.x + CellSize;
            pawnPosition.y = position_.y;
            break;
        case 2:
            pawnPosition.y = position_.y - CellSize;
            pawnPosition.x = position_.x;
            break;
        case 3:
            pawnPosition.y = position_.y + CellSize;
            pawnPosition.x = position_.x;
            break;
        }
    } while(map_->IsWall(pawnPosition));

    scene_->AddGameObject(new Enemy6(pawnPosition, scene_, lem_, playerManager_, pm_, map_));
}