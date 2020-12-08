#include <fstream>
#include "SingleRoomMap.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"

SingleRoomMap::SingleRoomMap()
{}

SingleRoomMap::~SingleRoomMap()
{
    for (auto i : tileMapKeys_) LP::DeleteSprite(i);
}

void SingleRoomMap::Draw()
{
    for (auto i : tileMapKeys_) LP::DrawSprite(i);
}

void SingleRoomMap::SetMapArea(int width, int height)
{
    mapWidth_ = width;
    mapHeight_ = height;

    std::vector<int> resize(mapHeight_);
    map_.resize(mapWidth_, resize);
    objectMap_.resize(mapWidth_, resize);
}

std::vector<sf::IntRect> SingleRoomMap::GetMapArea() const
{
    std::vector<sf::IntRect> temp;
    temp.push_back(sf::IntRect(0, 0, mapWidth_, mapHeight_));
    return temp;
}

bool SingleRoomMap::IsWall(sf::Vector2f worldCoordinate)
{
    int terrainID = GetLocation(worldCoordinate);
    if (terrainID >= 40) return false;
    else return true;
}

int SingleRoomMap::GetLocation(sf::Vector2f worldCoordinate)
{
    int mapX = (int)(worldCoordinate.x / CellSize);
    int mapY = (int)(worldCoordinate.y / CellSize);

    if (mapX < 0 || mapX >= mapWidth_*10 || mapY < 0 || mapY >= mapHeight_*10)
        return 0;

    return map_[mapX][mapY];
}

void SingleRoomMap::LoadTilesFromCSC(const std::string& CSCFilePath)
{
    std::ifstream mapData(CSCFilePath);
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
            if (map_[x][y] != -1) 
            {
                tileMapKeys_.push_back(LP::SetSprite(tile_map, sf::Vector2f(x*CellSize, y*CellSize), CellSize, CellSize, map_[x][y]));
            }
        }
    }

    mapData.close();
}

void SingleRoomMap::LoadDetailsFromCSC(const std::string& CSCFilePath)
{
    std::ifstream detailData(CSCFilePath);
    int value;
    char dummy;

    for (int y = 0; y < mapHeight_; y++)
    {
        for (int x = 0; x < mapWidth_; x++)
        {
            detailData >> value;
            if (x < mapWidth_ - 1) 
            {
                detailData >> dummy;
            }
            if (value != -1) 
            {
                tileMapKeys_.push_back(LP::SetSprite(tile_map_details, sf::Vector2f(x*CellSize, y*CellSize), CellSize, CellSize, value));
            }
        }
    }

    detailData.close();
}

void SingleRoomMap::LoadObjectsFromCSC(const std::string& CSCFilePath)
{
    std::ifstream objectData(CSCFilePath);
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
        }
    }

    objectData.close();

    PlaceObjectsUsingObjectMap(objectMap_);
}