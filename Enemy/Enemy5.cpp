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
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);
    numOfBeatsBetweenAttacks_ = 4;
    flip_ = false;

    ed_ = lem_->Add(HP_, HP_, 1, 0);

    enemyRectangle_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);
    LP::SetRectangleColor(enemyRectangle_, 0, 255, 0, 255);
    StorePosition();
    //timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 4 / 2;
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Enemy5::~Enemy5()
{
    // for (auto i : enemySprite_)
    // {
    //     LP::DeleteSprite(i);
    // }

    LP::DeleteRectangle(enemyRectangle_);
}

void Enemy5::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (!hasMoved_) 
        {
            beatCount_++;
        }
        if (state_ == Angry && beatCount_ >= numOfBeatsBetweenAttacks_)
        {
            beatCount_ = 0;
            SpawnPawn();
        }
        hasMoved_ = true;
    }
    else hasMoved_ = false;

    //AnimationHandle(delta_time, beat_time);

    //velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(position_);
}

void Enemy5::Draw()
{
    LP::DrawRectangle(enemyRectangle_);
}

void Enemy5::DelayedDraw()
{
    if (GetInRangeOfPlayer()) arrow_->Draw();
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
        arrow_->TakeDamage();
        ed_->hp_--;
        if (ed_->hp_ <= 0)
        {
            pm_->EnemyDeath(position_.x+imageWidth_/2, position_.y+imageHeight_/2);
            if (rand() % 10 == 0) scene_->AddGameObject(new Money(position_, playerManager_, pm_));
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
{}

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