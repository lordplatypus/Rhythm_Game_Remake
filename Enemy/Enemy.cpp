#include "Enemy.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include "../Item/Money.h"

Enemy::Enemy()
{}

Enemy::~Enemy()
{}

void Enemy::AnimationHandle(float delta_time, float beat_time)
{}

void Enemy::TakeDamage(const int damage)
{
    if (damage == -1) return;
    if (damage == arrow_->GetCurrentArrow())
    {
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

void Enemy::CheckMoveLocation()
{
    if (map_->IsWall(position_)) position_ = GetPrevPosition();
}

void Enemy::SetPerception(const float perception)
{
    ed_->range_ = perception;
}

float Enemy::GetPerception() const
{
    return ed_->range_ + lem_->GetRangeModifier();
}

void Enemy::SetInRangeOfPlayer(const bool inRangeOfPlayer)
{
    inRangeOfPlayer_ = inRangeOfPlayer;
}

bool Enemy::GetInRangeOfPlayer() const
{
    return inRangeOfPlayer_;
}

void Enemy::Kill()
{
    isDead_ = true;
    delete arrow_;
}