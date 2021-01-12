#include "Room.h"
#include <fstream>
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Room::Room(RoomData* roomData) : roomData_{roomData}
{
    SetRoomMap();

    if (PlayerRoom()) SetPlayerRand();
    if (StairRoom()) SetStairRand(GetTransitionID());
    if (!BlockRandSpawn()) SetEnemiesRand(GetEnemyCount());
}

Room::~Room()
{
    End();
}

void Room::Draw(sf::RenderWindow& render_window)
{
    // for (int i = 0; i < tileMapKeys_.size(); i++)
    // {
    //     LP::DrawSprite(tileMapKeys_[i]);
    // }
    render_window.draw(roomTileMap_);
}

RoomData* Room::GetRoomData() const
{
    return roomData_;
}

const std::string& Room::GetRoomDataLocation() const
{
    return roomData_->roomDataLocation_;
}

const sf::IntRect& Room::GetRoomArea() const
{
    return roomData_->roomArea_;
}

sf::IntRect Room::GetRoomAreaWorldCoordinates() const
{
    return sf::IntRect(roomData_->roomArea_.left * CellSize, roomData_->roomArea_.top * CellSize, roomData_->roomArea_.width * CellSize, roomData_->roomArea_.height * CellSize);
}

sf::Vector2i Room::GetRoomPosition() const
{
    return roomData_->GetPosition();
}

sf::Vector2i Room::GetRoomPositionWorldCoordinates() const
{
    return sf::Vector2i(roomData_->GetPosition().x * CellSize, roomData_->GetPosition().y * CellSize);
}

sf::Vector2i Room::GetRoomSize() const
{
    return roomData_->GetSize();
}

const std::vector<sf::Vector2i>& Room::GetHallPoints() const
{
    return roomData_->hallPoints_;
}

const int Room::GetEnemyCount() const
{
    return roomData_->enemyCount_;
}

const int Room::GetTransitionID() const
{
    return roomData_->transitionID_;
}

const bool Room::PlayerRoom() const
{
    return roomData_->playerRoom_;
}

const bool Room::StairRoom() const
{
    return roomData_->stairRoom_;
}

const bool Room::BlockRandSpawn() const
{
    return roomData_->blockRandSpawn_;
}

void Room::SetRoomMap()
{
    SetRoomMap(GetRoomDataLocation());
}

void Room::SetRoomMap(const std::string& roomDataLocation)
{
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

std::vector<std::vector<int>> Room::GetRoomMap() const
{
    return roomMap_;
}

// void Room::SetHallPoints(std::vector<sf::Vector2i> hallPoints)
// {
//     roomData_->hallPoints_ = hallPoints;
// }

// void Room::SetHallPoint(sf::Vector2i hallPoint)
// {
//     roomData_->hallPoints_.push_back(hallPoint);
// }

// std::vector<sf::Vector2i> Room::GetHallPoints() const
// {
//     return roomData_->hallPoints_;
// }

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

void Room::SetTiles()
{
    roomTileMap_ = LP::SetTileMap(tile_map, sf::Vector2u(32, 32), roomMap_, sf::Vector2f(GetRoomPosition().x * CellSize, GetRoomPosition().y * CellSize), GetRoomSize().x, GetRoomSize().y);
}

void Room::SetRoomObjectMap(const std::string& roomObjectDataLocation)
{
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

void Room::SetEnemiesRand(int numOfEnemies)
{
    if (roomData_->blockRandSpawn_) return;

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

std::vector<std::vector<int>> Room::GetRoomObjectMap() const
{
    return roomObjectMap_;
}

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

void Room::End()
{
    delete roomData_;
}