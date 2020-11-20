#include "Map.h"
#include <fstream>
#include "../Player/Roboko.h"
#include "../Item/Money.h"
#include "../Transition/Transition.h"

Map::Map()
{}

Map::~Map()
{}

void Map::CreateMap()
{}

void Map::PlaceObjects()
{}

void Map::PlaceObjectsUsingObjectMap(std::vector<std::vector<int> > objectMap)
{
    for (int y = 0; y < mapHeight_; y++)
    {
        for (int x = 0; x < mapWidth_; x++)
        {
            if (objectMap_[x][y] == -1) continue;
            else if (objectMap_[x][y] == 0) scene_->AddGameObject(new Roboko(sf::Vector2f(CellSize * x, CellSize * y), scene_, camera_, playerManager_, transitionManager_, this));
            else if (objectMap_[x][y] < 200) PlaceItem(objectMap_[x][y], sf::Vector2f(CellSize * x, CellSize * y));
            else if (objectMap_[x][y] < 300) PlaceTransition(objectMap_[x][y], sf::Vector2f(CellSize * x, CellSize * y));
        }
    }
}

void Map::Draw()
{}

int Map::GetLocation(sf::Vector2f worldCoordinate)
{
    int mapX = (int)(worldCoordinate.x / CellSize);
    int mapY = (int)(worldCoordinate.y / CellSize);

    if (mapX < 0 || mapX >= mapWidth_*10 || mapY < 0 || mapY >= mapHeight_*10)
        return 0;

    return map_[mapX][mapY];
}

bool Map::IsWall(sf::Vector2f worldCoordinate)
{
    int terrainID = GetLocation(worldCoordinate);
    if (terrainID >= 40) return false;
    else return true;
}

bool Map::IsStair(sf::Vector2f worldCoordinate)
{
    int terrainID = GetLocation(worldCoordinate);
    if (terrainID == 40) return true;
    return false;
}

void Map::PlaceItem(int num, sf::Vector2f position)
{
    switch (num)
    {
        case 100:
        scene_->AddGameObject(new Money(position, playerManager_, particleManager_));
        break;

        default:
        break;
    }
}

void Map::PlaceTransition(int num, sf::Vector2f position)
{
    std::string transitionTo = "";
    switch (num)
    {
        case 200:
        transitionTo = "Title";
        break;

        case 201:
        transitionTo = "Lobby";
        break;

        case 203:
        transitionTo = "BPM";
        break;

        case 206:
        transitionTo = "Test";
        break;

        case 207:
        transitionTo = "JunkYard";
        break;

        default:
        transitionTo = "Title";
        break;
    }
    scene_->AddGameObject(new Transition(transitionManager_, transitionTo, position, false, scene_, particleManager_));



//     if (name == "Title") return 200;
//     else if (name == "Lobby") return 201;
//     else if (name == "ClassSelect") return 202;
//     else if (name == "SetBPM") return 203;
//     else if (name == "MusicSelect") return 204;
//     else if (name == "Tutorial") return 205;
//     else if (name == "Test") return 206;
//     else if (name == "JunkYard") return 207;
//     else if (name == "Stage1_1") return 208;
//     else if (name == "Stage1_2") return 209;
//     else if (name == "Stage1_3") return 210;
}