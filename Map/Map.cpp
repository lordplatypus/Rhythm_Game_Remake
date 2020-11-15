#include "Map.h"
#include <fstream>

Map::Map()
{}

Map::~Map()
{}

void Map::CreateMap()
{}

void Map::PlaceObjects()
{}

// void Map::Update()
// {}

void Map::Draw()
{}

int Map::GetLocation(float worldX, float worldY)
{
    int mapX = (int)(worldX / CellSize);
    int mapY = (int)(worldY / CellSize);

    if (mapX < 0 || mapX >= mapWidth_*10 || mapY < 0 || mapY >= mapHeight_*10)
        return 0;

    return map_[mapX][mapY];
}

bool Map::IsWall(float worldX, float worldY)
{
    int terrainID = GetLocation(worldX, worldY);
    if (terrainID >= 40) return false;
    else return true;
}

bool Map::IsStair(sf::Vector2f worldCoordinate)
{
    int terrainID = GetLocation(worldCoordinate.x, worldCoordinate.y);
    if (terrainID == 40) return true;
    return false;
}