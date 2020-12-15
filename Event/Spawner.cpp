#include "Spawner.h"

Spawner::Spawner(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, Scene* scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    target_ = lockTarget;
    camera_ = camera;
    transitionManager_ = transitionManager;
    tag_ = "Event";
    name_ = "Spawner";
    position_ = sf::Vector2f(0.0f, 0.0f);

    spawner_ = new Enemy5(scene->FindGameObject(lockTarget, false)->GetPosition(), scene, lem, playerManager, pm, map);
    scene->AddGameObject(spawner_);

    SetInstructionText("Defeat The Spawner: Active");

    Lock();
}

void Spawner::Update(float delta_time, float beat_time)
{
    DisplayInstructionsText(delta_time);
    if (done_) return;

    if (spawner_->IsDead()) 
    {
        Unlock();
        done_ = true;
        SetInstructionTextString("Defeat The Spawner: Inactive");
    }
}