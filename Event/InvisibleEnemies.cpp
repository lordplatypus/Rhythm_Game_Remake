#include "InvisibleEnemies.h"

InvisibleEnemies::InvisibleEnemies(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, ParticleManager* pm, Map* map, LocalEnemyManager* lem)
{
    target_ = lockTarget;
    camera_ = camera;
    transitionManager_ = transitionManager;
    playerManager_ = playerManager;
    scene_ = scene;
    lem_ = lem;
    pm_ = pm;
    map_ = map;
    tag_ = "Event";
    name_ = "Invisible";
    position_ = sf::Vector2f(0.0f, 0.0f);

    PlaceGenerator();
    lem_->SetTempVisibility(false);

    SetInstructionText("Enemies Are Invisible\nGenerator: Active");

    Lock();
}

void InvisibleEnemies::Update(float delta_time, float beat_time)
{
    DisplayInstructionsText(delta_time);
    if (generatorDestroyed_) return;

    if (generator_ == nullptr || generator_->IsDead())
    {
        EventTrigger();
    }
}

void InvisibleEnemies::EventTrigger()
{
    generatorDestroyed_ = true;
    lem_->SetTempVisibility(true);
    SetInstructionTextString("Enemies Are Invisible\nGenerator: Inactive");
    Unlock();
}

void InvisibleEnemies::PlaceGenerator()
{
    bool done = false;
    int failsafe = 0;
    while (!done)
    {
        sf::IntRect roomArea = map_->GetMapArea()[rand() % (map_->GetMapArea().size() - 1) + 1];
        sf::Vector2f generatorPosition = sf::Vector2f((rand() % roomArea.width + roomArea.left) * CellSize, (rand() % roomArea.height + roomArea.top) * CellSize);
        if (!map_->IsWall(generatorPosition))
        {
            done = true;
            generator_ = new Generator(generatorPosition, scene_, lem_, playerManager_, pm_, map_);
            scene_->AddGameObject(generator_);
        }

        failsafe++;
        if (failsafe >= 10)
        {
            done = true;
        }
    }
}