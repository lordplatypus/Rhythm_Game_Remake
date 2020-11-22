#include "DefeatEnemies.h"

DefeatEnemies::DefeatEnemies(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, LocalEnemyManager* lem)
{
    target_ = lockTarget;
    camera_ = camera;
    transitionManager_ = transitionManager;
    lem_ = lem;
    tag_ = "Event";
    name_ = "DefeatEnemies";
    position_ = sf::Vector2f(0.0f, 0.0f);

    numToDefeat_ = rand() % lem_->GetEnemyCount() + 1;
    SetInstructionText("Defeat " + std::to_string(numToDefeat_) + " Enemies: " + std::to_string(lem_->GetEnemyDeathCount()));

    Lock();
}

void DefeatEnemies::Update(float delta_time, float beat_time)
{
    DisplayInstructionsText(delta_time);

    if (defeatedNum_ >= numToDefeat_) return;

    if (defeatedNum_ != lem_->GetEnemyDeathCount())
    {
        defeatedNum_ = lem_->GetEnemyDeathCount();
        if (defeatedNum_ >= numToDefeat_) 
        {
            SetInstructionTextString("Defeat " + std::to_string(numToDefeat_) + " Enemies: Cleared");
            Unlock();
        }
        else SetInstructionTextString("Defeat " + std::to_string(numToDefeat_) + " Enemies: " + std::to_string(defeatedNum_));
    }
}