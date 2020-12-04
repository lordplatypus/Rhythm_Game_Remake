#include "FindKeys.h"
#include "../Item/Key.h"

FindKeys::FindKeys(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, ParticleManager* pm, Map* map)
{
    target_ = lockTarget;
    camera_ = camera;
    transitionManager_ = transitionManager;
    playerManager_ = playerManager;
    scene_ = scene;
    pm_ = pm;
    map_ = map;
    tag_ = "Event";
    name_ = "Key";
    position_ = sf::Vector2f(0.0f, 0.0f);

    PlaceKeys();

    SetInstructionText("Find The Keys: " + std::to_string(keyCounter_) + " Left");

    Lock();
}

void FindKeys::Update(float delta_time, float beat_time)
{
    DisplayInstructionsText(delta_time);
}

void FindKeys::PickUpKey()
{
    keyCounter_--;
    if (keyCounter_ <= 0) 
    {
        SetInstructionTextString("Find The Keys: Cleared");
        Unlock();
    }
    else SetInstructionTextString("Find The Keys: " + std::to_string(keyCounter_) + " Left");
}

void FindKeys::PlaceKeys()
{
    int numOfKeys = rand() % 5 + 1;

    for (int i = 0; i < numOfKeys; i++)
    {
        bool done = false;
        int failsafe = 0;
        while (!done)
        {
            sf::IntRect roomArea = map_->GetMapArea()[rand() % (map_->GetMapArea().size() - 1) + 1];
            sf::Vector2f keyPosition = sf::Vector2f((rand() % roomArea.width + roomArea.left) * CellSize, (rand() % roomArea.height + roomArea.top) * CellSize);
            if (!map_->IsWall(keyPosition))
            {
                done = true;
                scene_->AddGameObject(new Key(keyPosition, playerManager_, pm_, this));
                keyCounter_++;
            }

            failsafe++;
            if (failsafe >= 10)
            {
                done = true;
            }
        }
    }
}