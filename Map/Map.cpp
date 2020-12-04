#include "Map.h"
#include <fstream>
//Objects
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
//Rooms
#include "../Map/Room1.h"
#include "../Map/Room2.h"
#include "../Map/Room3.h"
#include "../Map/Junkyard.h"

Map::Map()
{}

Map::~Map()
{}

void Map::Draw()
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

void Map::CreateMapWithRooms(int numOfRooms, const std::string& transitionTo)
{
    SetRooms(numOfRooms);
    SetHalls();
    SetTransition(transitionTo);
    BuildMapBlueprint();
}

void Map::SetRooms(int numOfRooms)
{
    sf::Vector2i currentPosition(0, 0);
    //Room* prevRoom = new Room1(currentPosition);
    //rooms_.push_back(prevRoom);
    Room* prevRoom = SetGetRandRoom(currentPosition, 0, numOfRooms);

    //prevRoom->SetPlayerRand();

    for (int i = 1; i < numOfRooms; i++)
    {
        int temp = rand() % 4;
        // Room* currentRoom = nullptr;
        // if (temp == 0) currentRoom = new Room1(currentPosition);
        // else if (temp == 1) currentRoom = new Room2(currentPosition);
        // else if (temp == 2) currentRoom = new Room3(currentPosition);
        // else currentRoom = new Junkyard(currentPosition);
        // rooms_.push_back(currentRoom);
        Room* currentRoom = SetGetRandRoom(currentPosition, i, numOfRooms);
        bool done = false;
        int changeRoom = 0;
        while (!done)
        {
            changeRoom++;
            if (changeRoom >= 10)
            {
                changeRoom = 0;
                rooms_.pop_back();
                currentRoom = SetGetRandRoom(currentPosition, i, numOfRooms);
            }

            currentPosition = sf::Vector2i(prevRoom->GetRoomArea().left, prevRoom->GetRoomArea().top);
            //sf::Vector2i prevRoomHallPoint = prevRoom->GetHallPoints()[rand() % prevRoom->GetHallPoints().size()];

            sf::Vector2i hallPoint = prevRoom->GetHallPoints()[rand() % prevRoom->GetHallPoints().size()] + prevRoom->GetRoomPosition();

            if (hallPoint.x == prevRoom->GetRoomArea().left)//left
            {
                currentPosition = sf::Vector2i(hallPoint.x - currentRoom->GetRoomArea().width, hallPoint.y - 4);
                hallPoint.x--; //makes the calc in the for loop easier
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.x == prevRoom->GetRoomArea().left + prevRoom->GetRoomArea().width - 1)//right
            {
                hallPoint.x++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x, hallPoint.y - 4);
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->GetRoomArea().top)//top
            {
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y - currentRoom->GetRoomArea().height);
                hallPoint.y--; //makes the calc in the for loop easier
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->GetRoomArea().top + prevRoom->GetRoomArea().height - 1)//bottom
            {
                hallPoint.y++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y);
                for (auto i : currentRoom->GetHallPoints())
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            if (!done) continue;

            currentRoom->SetRoomPosition(currentPosition);
            for (int i = 0; i < rooms_.size() - 1; i++)
            {
                if (currentRoom->GetRoomArea().intersects(rooms_[i]->GetRoomArea())) 
                {
                    done = false;
                    currentRoom->SetRoomPosition(prevRoom->GetRoomPosition());
                }
            }
        }
        prevRoom = currentRoom;
    }
}

Room* Map::SetGetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum)
{
    Room* room;

    if (roomBuildOrderNum == 0)
    {
        room = new Room1(position, true, true);
        rooms_.push_back(room);
        return room;
    }

    bool done = false;
    int failsafe = 0;
    while (!done)
    {
        failsafe++;
        if (failsafe >= 100) 
        {
            room = new Room1(position);
            rooms_.push_back(room);
            return room;
        } 

        int randRoom = rand() % 4;
        if (randRoom == 0) 
        {
            room = new Room1(position);
            done = true;
        }
        else if (randRoom == 1) 
        {
            room = new Room2(position);
            done = true;
        }
        else if (randRoom == 2) 
        {
            room = new Room3(position);
            done = true;
        }
        else if (randRoom == 3 && roomBuildOrderNum != 0 && roomBuildOrderNum != maxRoomNum - 1) 
        {
            room = new Junkyard(position);
            done = true;
        }
    }
    rooms_.push_back(room);
    return room;
}

void Map::SetHalls()
{
    for (auto i = rooms_.begin(); i != rooms_.end(); i++)
    {
        for (auto j = next(i); j != rooms_.end(); j++)
        {
            for (auto current : (*i)->GetHallPoints())
            {
                sf::Vector2i wc_current = current + (*i)->GetRoomPosition(); //world coordinate
                for (auto other : (*j)->GetHallPoints())
                {
                    sf::Vector2i wc_other = other + (*j)->GetRoomPosition(); //world coordinate
                    if (sf::Vector2i(wc_current.x - 1, wc_current.y) == wc_other) //left
                    {
                        (*i)->CreateLeftHall(current);
                        (*j)->CreateRightHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x + 1, wc_current.y) == wc_other) //right
                    {
                        (*i)->CreateRightHall(current);
                        (*j)->CreateLeftHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x, wc_current.y - 1) == wc_other) //top
                    {
                        (*i)->CreateUpHall(current);
                        (*j)->CreateDownHall(other);
                    }
                    else if (sf::Vector2i(wc_current.x, wc_current.y + 1) == wc_other) //bottom
                    {
                        (*i)->CreateDownHall(current);
                        (*j)->CreateUpHall(other);
                    }
                }
            }
        }
    }
}

void Map::SetTransition(const std::string& transitionTo)
{
    rooms_.back()->SetStairRand(transitionManager_->GetSceneID(transitionTo));
}

void Map::BuildMapBlueprint()
{
    for (auto i : rooms_)
    {
        i->SetTiles();
        PlaceObjectsInRoom(i->GetRoomArea(), i->GetRoomObjectMap());
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