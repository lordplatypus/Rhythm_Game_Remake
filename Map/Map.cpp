#include "Map.h"
#include <fstream>
#include "../Player/Roboko.h"
#include "../Enemy/Enemy1.h"
#include "../Enemy/Enemy2.h"
#include "../Enemy/Enemy3.h"
#include "../Enemy/Enemy4.h"
#include "../Enemy/Enemy5.h"
#include "../Enemy/Enemy6.h"
#include "../Item/Money.h"
#include "../Item/MaxHPUp.h"
#include "../Item/ReduceCooldown.h"
#include "../Item/Heal1.h"
#include "../Item/PerceptionUp.h"
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
            if (objectMap[x][y] == -1) continue;
            else if (objectMap[x][y] == 0) scene_->AddGameObject(new Roboko(sf::Vector2f(CellSize * x, CellSize * y), scene_, camera_, playerManager_, transitionManager_, particleManager_, this));
            else if (objectMap[x][y] < 100) PlaceEnemy(objectMap[x][y], sf::Vector2f(CellSize * x, CellSize * y));
            else if (objectMap[x][y] < 200) PlaceItem(objectMap[x][y], sf::Vector2f(CellSize * x, CellSize * y));
            else if (objectMap[x][y] < 300) PlaceTransition(objectMap[x][y], sf::Vector2f(CellSize * x, CellSize * y));
        }
    }
}

void Map::PlaceObjectsInRoom(sf::IntRect roomArea, std::vector<std::vector<int> > objectMap)
{
    for (int y = 0; y < roomArea.height; y++)
    {
        for (int x = 0; x < roomArea.width; x++)
        {
            if (objectMap[x][y] == -1) continue;
            sf::Vector2f worldPosition = sf::Vector2f((x + roomArea.left) * CellSize, (y + roomArea.top) * CellSize);

            if (objectMap[x][y] == 0) scene_->AddGameObject(new Roboko(worldPosition, scene_, camera_, playerManager_, transitionManager_, particleManager_, this));
            else if (objectMap[x][y] < 100) PlaceEnemy(objectMap[x][y], worldPosition);
            else if (objectMap[x][y] < 200) PlaceItem(objectMap[x][y], worldPosition);
            else if (objectMap[x][y] < 300) PlaceTransition(objectMap[x][y], worldPosition);
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

void Map::PlaceEnemy(int num, sf::Vector2f position)
{
    switch (num)
    {
        case 1:
        scene_->AddGameObject(new Enemy1(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        case 2:
        scene_->AddGameObject(new Enemy2(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        case 3:
        scene_->AddGameObject(new Enemy3(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        case 4:
        scene_->AddGameObject(new Enemy4(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        case 5:
        scene_->AddGameObject(new Enemy5(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        case 6:
        scene_->AddGameObject(new Enemy6(position, scene_, localEnemyManager_, playerManager_, particleManager_, this));
        break;

        default:
        break;
    }
}

void Map::PlaceItem(int num, sf::Vector2f position)
{
    switch (num)
    {
        case 100:
        scene_->AddGameObject(new Money(position, playerManager_, particleManager_));
        break;

        case 101:
        scene_->AddGameObject(new MaxHPUp(position, playerManager_, particleManager_));
        break;

        case 102:
        scene_->AddGameObject(new ReduceCooldown(position, playerManager_, particleManager_));
        break;

        case 103:
        scene_->AddGameObject(new Heal1(position, playerManager_, particleManager_));
        break;

        case 104:
        scene_->AddGameObject(new PerceptionUp(position, playerManager_, particleManager_));
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

        case 204:
        transitionTo = "MusicSelect";
        break;

        case 206:
        transitionTo = "Test";
        break;

        case 207:
        transitionTo = "JunkYard";
        break;

        case 208:
        transitionTo = "Stage1_1";
        break;

        case 209:
        transitionTo = "Stage1_2";
        break;

        case 210:
        transitionTo = "Stage1_3";
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