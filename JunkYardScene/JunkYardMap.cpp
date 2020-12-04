#include <fstream>
#include "JunkYardMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"

JunkYardMap::JunkYardMap(Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;
    mapWidth_ = 9;
    mapHeight_ = 14;
    SetMapArea(9, 14);
    
    LoadTilesFromCSC("./Resources/Map/Junk_Yard_Map_Factory_Main.csv");
    LoadObjectsFromCSC("./Resources/Map/Junk_Yard_Map_Factory_Object.csv");


    //CreateMap();
    //PlaceObjects();
}

void JunkYardMap::LoadObjectsFromCSC(const std::string& CSCFilePath)
{
    std::ifstream objectData(CSCFilePath);
    int value;
    char dummy;

    for (int y = 0; y < mapHeight_; y++)
    {
        for (int x = 0; x < mapWidth_; x++)
        {
            objectData >> objectMap_[x][y];
            if (x < mapWidth_ - 1) 
            {
                objectData >> dummy;
            }

            if (objectMap_[x][y] == 100) objectMap_[x][y] = GenerateItem();
            if (objectMap_[x][y] == 201) objectMap_[x][y] = PrevScene();
        }
    }

    PlaceObjectsUsingObjectMap(objectMap_);
}

int JunkYardMap::GenerateItem()
{
    bool cont = true;
    int randItem = 0;
    do
    {
        cont = true;
        randItem = rand() % 4 + 101;
        for (auto i : itemIDs_)
        {
            if (i == randItem) cont = false;
        }
    } while (!cont);
    
    itemIDs_.push_back(randItem);
    return randItem;
}

int JunkYardMap::PrevScene()
{
    return transitionManager_->GetSceneID(transitionManager_->GetPrevScene());
}