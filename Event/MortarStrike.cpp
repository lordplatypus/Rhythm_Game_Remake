#include "MortarStrike.h"
#include "../Enemy/Mortar.h"
#include "../Engine/MP.h"

MortarStrike::MortarStrike(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, LocalEnemyManager* lem, ParticleManager* pm, Map* map)
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
    name_ = "Mortar";
    position_ = sf::Vector2f(0.0f, 0.0f);
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    PlaceGenerator();

    SetInstructionText("Mortor Strike - Generator: Active");

    Lock();
}

void MortarStrike::Update(float delta_time, float beat_time)
{
    DisplayInstructionsText(delta_time);

    if (generatorDestroyed_) return;

    if (!input_ && beat_time <= windowOfInput_)
    {
        input_ = true;
        fireCountDown_--;
        if (fireCountDown_ <= 0) 
        {
            fireCountDown_ = 10;
            FireMortar();
        }
    }
    else if (beat_time > windowOfInput_)
    {
        input_ = false;
    }

    if (generator_ == nullptr || generator_->IsDead())
    {
        EventTrigger();
    }
}

void MortarStrike::EventTrigger()
{
    generatorDestroyed_ = true;
    SetInstructionTextString("Mortor Strike - Generator: Inactive");
    Unlock();
}

void MortarStrike::PlaceGenerator()
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

void MortarStrike::FireMortar()
{
    sf::Vector2f playerPosition = scene_->FindGameObject("Player")->GetPosition();
    int direction = rand() % 5;
    switch (direction)
    {
        case 0:
        playerPosition.x -= CellSize;
        break;

        case 1:
        playerPosition.x += CellSize;
        break;

        case 2:
        playerPosition.y -= CellSize;
        break;

        case 3:
        playerPosition.y += CellSize;
        break;

        default:
        break;
    }

    if (map_->IsWall(playerPosition)) playerPosition = scene_->FindGameObject("Player")->GetPosition();
    playerPosition.x += 16.0f;
    playerPosition.y += 16.0f;
    scene_->AddGameObject(new Mortar(playerPosition, scene_, lem_, pm_));
}