#include <SFML/Graphics.hpp>
#include <fstream>
#include "TitleMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"

TitleMap::TitleMap(Scene *scene) : scene_{scene}
{
    mapWidth_ = 60;
    mapHeight_ = 10;

    std::vector<int> resize(mapHeight_);
    map_.resize(mapWidth_, resize);

    CreateMap();
    DetailMap();
}

TitleMap::~TitleMap()
{
    for (auto i : tileMapKeys_) LP::DeleteSprite(i);
}

void TitleMap::CreateMap()
{
    std::ifstream mapData("./Resources/Map/Title_Map_Factory_Main.csv");
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

void TitleMap::DetailMap()
{
    std::ifstream mapData("./Resources/Map/Title_Map_Factory_Detail.csv");
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

void TitleMap::PlaceObjects()
{}

void TitleMap::Draw()
{
    for (auto i : tileMapKeys_) LP::DrawSprite(i);
}