#include <fstream>
#include "TestMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"

TestMap::TestMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;
    MapSize_ = 10;
    mapWidth_ = 10;
    mapHeight_ = 10;

    std::vector<int> resize(MapSize_);
    map_.resize(MapSize_, resize);
    objectMap_.resize(MapSize_, resize);

    CreateMap();
    DetailMap();
    PlaceObjects();
}

TestMap::~TestMap()
{
    int tileMapKeysLength = tileMapKeys_.size();
    for (int i = 0; i < tileMapKeysLength; i++)
    {
        LP::DeleteSprite(tileMapKeys_[i]);
    }
}

void TestMap::CreateMap()
{
    std::ifstream mapData("./Resources/Map/Test_Map_Factory_Main.csv");
    int value;
    char dummy;

    for (int y = 0; y < MapSize_; y++)
    {
        for (int x = 0; x < MapSize_; x++)
        {
            mapData >> map_[x][y];
            if (x < MapSize_ - 1) 
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

void TestMap::DetailMap()
{
    std::ifstream mapData("./Resources/Map/Test_Map_Factory_Detail.csv");
    int value;
    char dummy;

    for (int y = 0; y < mapHeight_; y++)
    {
        for (int x = 0; x < mapWidth_; x++)
        {
            mapData >> value;
            if (x < mapWidth_ - 1) 
            {
                mapData >> dummy;
            }
            if (value == -1) continue;
            if (value != -1) 
            {
                tileMapKeys_.push_back(LP::SetSprite(tile_map_details, sf::Vector2f(x*CellSize, y*CellSize), CellSize, CellSize, value));
            }
        }
    }
}

void TestMap::PlaceObjects()
{
    std::ifstream objectData("./Resources/Map/Test_Map_Factory_Object.csv");
    int value;
    char dummy;

    for (int y = 0; y < MapSize_; y++)
    {
        for (int x = 0; x < MapSize_; x++)
        {
            objectData >> objectMap_[x][y];
            if (x < MapSize_ - 1) 
            {
                objectData >> dummy;
            }
        }
    }

    PlaceObjectsUsingObjectMap(objectMap_);
}

void TestMap::Draw()
{
    for (int i = 0; i < tileMapKeys_.size(); i++)
    {
        LP::DrawSprite(tileMapKeys_[i]);
    }
}