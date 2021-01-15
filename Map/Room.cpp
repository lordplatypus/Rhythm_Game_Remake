#include "Room.h"
#include <fstream>
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Room::Room(const std::string& name, const sf::IntRect& roomArea, const std::vector<sf::Vector2i>& hallPoints) :
           name_{name}, roomArea_{roomArea}, hallPoints_{hallPoints}
{}

Room::~Room()
{
    End();
}

void Room::Draw(sf::RenderWindow& render_window)
{
    render_window.draw(roomTileMap_);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Get Data
////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string& Room::GetRoomName() const
{
    return name_;
}

const sf::IntRect& Room::GetRoomArea() const
{
    return roomArea_;
}

sf::IntRect Room::GetRoomAreaWorldCoordinates() const
{
    return sf::IntRect(roomArea_.left * CellSize, roomArea_.top * CellSize, roomArea_.width * CellSize, roomArea_.height * CellSize);
}

sf::Vector2i Room::GetRoomPosition() const
{
    return sf::Vector2i(roomArea_.left, roomArea_.top);
}

sf::Vector2i Room::GetRoomPositionWorldCoordinates() const
{
    return GetRoomPosition() * CellSize;
}

sf::Vector2i Room::GetRoomSize() const
{
    return sf::Vector2i(roomArea_.width, roomArea_.height);
}

const std::vector<sf::Vector2i>& Room::GetHallPoints() const
{
    return hallPoints_;
}

// const int Room::GetEnemyCount() const
// {
//     return enemyCount_;
// }

// const int Room::GetTransitionID() const
// {
//     return transitionID_;
// }

// const bool Room::PlayerRoom() const
// {
//     return playerRoom_;
// }

// const bool Room::StairRoom() const
// {
//     return stairRoom_;
// }

// const bool Room::BlockRandSpawn() const
// {
//     return blockRandSpawn_;
// }

std::vector<std::vector<int>> Room::GetRoomMap() const
{
    return roomMap_;
}

std::vector<std::vector<int>> Room::GetRoomObjectMap() const
{
    return roomObjectMap_;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 1: Set Room Position
////////////////////////////////////////////////////////////////////////////////////////////////////
void Room::SetRoomPosition(const sf::Vector2i& position)
{
    roomArea_.left = position.x;
    roomArea_.top = position.y;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 2: set up maps (tilemap and object map) - includes building hallways between rooms
////////////////////////////////////////////////////////////////////////////////////////////////////
void Room::SetRoomTileMap(const std::string& roomDataLocation)
{
    std::vector<int> resize(GetRoomArea().height);
    roomMap_.resize(GetRoomArea().width, resize);

    std::ifstream mapData(roomDataLocation);
    char dummy;
    for (int y = 0; y < GetRoomSize().y; y++)
    {
        for (int x = 0; x < GetRoomSize().x; x++)
        {
            mapData >> roomMap_[x][y];
            if (roomMap_[x][y] == 32) roomMap_[x][y] = (rand() % 4) + 35; //random wall tiles
            if (roomMap_[x][y] == 41) roomMap_[x][y] = (rand() % 15) + 41; //random floor tiles
            if (x < GetRoomSize().x - 1)
            {//removes "," 
                mapData >> dummy;
            }
        }
    }
    mapData.close();
}

void Room::CreateLeftHall(sf::Vector2i position)
{
    roomMap_[position.x][position.y - 2] = 8;
    roomMap_[position.x][position.y - 1] = 32;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 2] = 4;
}

void Room::CreateRightHall(sf::Vector2i position)
{
    roomMap_[position.x][position.y - 2] = 7;
    roomMap_[position.x][position.y - 1] = 32;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 2] = 3;
}

void Room::CreateUpHall(sf::Vector2i position)
{
    roomMap_[position.x - 2][position.y] = 8;
    roomMap_[position.x - 1][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x + 1][position.y] = (rand() % 15) + 41;
    roomMap_[position.x + 2][position.y] = 7;

    roomMap_[position.x - 1][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x + 1][position.y + 1] = (rand() % 15) + 41;
}

void Room::CreateDownHall(sf::Vector2i position)
{
    roomMap_[position.x - 2][position.y] = 4;
    roomMap_[position.x - 1][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x + 1][position.y] = (rand() % 15) + 41;
    roomMap_[position.x + 2][position.y] = 3;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 3: Set up object map - not "physically" placing down objects, just inputing ID's
////////////////////////////////////////////////////////////////////////////////////////////////////
void Room::SetRoomObjectMap(const std::string& roomObjectDataLocation)
{
    std::vector<int> resize(GetRoomArea().height);
    roomObjectMap_.resize(GetRoomArea().width, resize);

    std::ifstream mapData(roomObjectDataLocation);
    char dummy;
    for (int y = 0; y < GetRoomSize().y; y++)
    {
        for (int x = 0; x < GetRoomSize().x; x++)
        {
            mapData >> roomObjectMap_[x][y];
            if (roomObjectMap_[x][y] == 32) roomObjectMap_[x][y] = (rand() % 4) + 35; //random wall tiles
            if (roomObjectMap_[x][y] == 41) roomObjectMap_[x][y] = (rand() % 15) + 41; //random floor tiles
            if (x < GetRoomSize().x - 1) 
            {//removes "," 
                mapData >> dummy;
            }
        }
    }
    mapData.close();
}

void Room::SetRoomObjectMapNull()
{
    std::vector<int> resize(GetRoomArea().height);
    roomObjectMap_.resize(GetRoomArea().width, resize);

    for (int y = 0; y < GetRoomSize().y; y++)
    {
        for (int x = 0; x < GetRoomSize().x; x++)
        {
            roomObjectMap_[x][y] = -1;
        }
    }
}

void Room::SetObject(sf::Vector2i objectPosition, int objectID)
{
    roomObjectMap_[objectPosition.x][objectPosition.y] = objectID;
}

void Room::SetPlayerRand()
{
    bool done = false;
    int failsafe = 0;
    while (!done)
    {
        failsafe++;
        if (failsafe >= 100) return;

        int x = (rand() % (GetRoomSize().x - 3)) + 1;
        int y = (rand() % (GetRoomSize().y - 4)) + 2;
        if (roomMap_[x][y] >= 40 && roomObjectMap_[x][y] == -1) 
        {
            done = true;
            roomObjectMap_[x][y] = 0;
        }
    }
}

void Room::SetStair(sf::Vector2i stairPosition, int transitionLocID)
{
    roomMap_[stairPosition.x][stairPosition.y] = 40;
    roomObjectMap_[stairPosition.x][stairPosition.y] = transitionLocID;

}

void Room::SetStairRand(int transitionLocID)
{
    bool done = false;
    int failsafe = 0;
    while (!done)
    {
        failsafe++;
        if (failsafe >= 100) return;

        int x = (rand() % (GetRoomSize().x - 3)) + 1;
        int y = (rand() % (GetRoomSize().y - 4)) + 2;
        if (roomMap_[x][y] > 40) 
        {
            done = true;
            roomMap_[x][y] = 40;
            roomObjectMap_[x][y] = transitionLocID;
        }
    }
}

void Room::SetEnemiesRand(int numOfEnemies)
{
    int done = 0;
    int failsafe = 0;
    while (done < numOfEnemies)
    {
        failsafe++;
        if (failsafe >= 100) return;

        int x = (rand() % (GetRoomSize().x - 3)) + 1;
        int y = (rand() % (GetRoomSize().y - 4)) + 2;
        if (roomMap_[x][y] > 40 && roomObjectMap_[x][y] == -1) 
        {
            done++;
            roomObjectMap_[x][y] = rand() % 4 + 1;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Step 4: Create Tilemap sprite
////////////////////////////////////////////////////////////////////////////////////////////////////
void Room::SetTileMapSprite()
{
    roomTileMap_ = LP::SetTileMap(tile_map, sf::Vector2u(32, 32), roomMap_, sf::Vector2f(GetRoomPosition().x * CellSize, GetRoomPosition().y * CellSize), GetRoomSize().x, GetRoomSize().y);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//For collision calcs
////////////////////////////////////////////////////////////////////////////////////////////////////
int Room::GetLocation(sf::Vector2i worldCoordinate)
{
    int mapX = worldCoordinate.x  / CellSize - GetRoomPosition().x;
    int mapY = worldCoordinate.y  / CellSize - GetRoomPosition().y;

    if (mapX < 0 || mapX >= GetRoomSize().x || mapY < 0 || mapY >= GetRoomSize().y)
        return 0;

    return roomMap_[mapX][mapY];
}

bool Room::IsWall(sf::Vector2i worldCoordinate)
{
    int terrainID = GetLocation(worldCoordinate);
    if (terrainID >= 40) return false;
    else return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//End
////////////////////////////////////////////////////////////////////////////////////////////////////
void Room::End()
{
}