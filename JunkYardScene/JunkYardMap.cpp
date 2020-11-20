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

    std::vector<int> resize(mapHeight_);
    map_.resize(mapWidth_, resize);
    objectMap_.resize(mapWidth_, resize);

    CreateMap();
    PlaceObjects();
}

JunkYardMap::~JunkYardMap()
{
    int tileMapKeysLength = tileMapKeys_.size();
    for (int i = 0; i < tileMapKeysLength; i++)
    {
        LP::DeleteSprite(tileMapKeys_[i]);
    }
}

void JunkYardMap::CreateMap()
{
    std::ifstream mapData("./Resources/Map/Junk_Yard_Map_Factory_Main.csv");
    int value;
    char dummy;

    for (int y = 0; y < mapHeight_; y++)
    {
        for (int x = 0; x < mapWidth_; x++)
        {
            mapData >> map_[x][y];
            if (x < mapWidth_ - 1) 
            {
                mapData >> dummy;
            }
            if (map_[x][y] == -1) continue;
            if (map_[x][y] != -1) 
            {
                tileMapKeys_.push_back(LP::SetSprite(tile_map, sf::Vector2f(x*CellSize, y*CellSize), CellSize, CellSize, map_[x][y]));
            }
        }
    }
}

void JunkYardMap::PlaceObjects()
{
    std::ifstream objectData("./Resources/Map/Junk_Yard_Map_Factory_Object.csv");
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

void JunkYardMap::Draw()
{
    for (int i = 0; i < tileMapKeys_.size(); i++)
    {
        LP::DrawSprite(tileMapKeys_[i]);
    }
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