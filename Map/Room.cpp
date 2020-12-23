#include "Room.h"
#include <fstream>
#include "../Engine/LP.h"
#include "../Assets/ID.h"

Room::Room()
{}

Room::~Room()
{
    End();
}

void Room::Draw()
{
    // for (int i = 0; i < tileMapKeys_.size(); i++)
    // {
    //     LP::DrawSprite(tileMapKeys_[i]);
    // }
    LP::DrawTileMap(roomTileMap_);
}

void Room::SetRoomArea(int left, int top, int width, int height)
{
    roomArea_ = sf::IntRect(left, top, width, height);

    std::vector<int> resize(roomHeight_);
    roomMap_.resize(roomWidth_, resize);
    roomObjectMap_.resize(roomWidth_, resize);
    SetRoomObjectMapNull();
}

void Room::SetRoomArea(sf::IntRect area)
{
    roomArea_ = area;
}

sf::IntRect Room::GetRoomArea() const
{
    return roomArea_;
}

void Room::SetRoomPosition(sf::Vector2i position)
{
    position_ = position;
    roomArea_ = sf::IntRect(position_.x, position_.y, roomWidth_, roomHeight_);
}

sf::Vector2i Room::GetRoomPosition() const
{
    return position_;
}

void Room::SetRoomMap()
{
    SetRoomMap(roomDataLocation_);
}

void Room::SetRoomMap(const std::string& roomDataLocation)
{
    std::ifstream mapData(roomDataLocation);
    char dummy;
    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomWidth_; x++)
        {
            mapData >> roomMap_[x][y];
            if (roomMap_[x][y] == 32) roomMap_[x][y] = (rand() % 4) + 35; //random wall tiles
            if (roomMap_[x][y] == 41) roomMap_[x][y] = (rand() % 15) + 41; //random floor tiles
            if (x < roomWidth_ - 1) 
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

void Room::SetHallPoints(std::vector<sf::Vector2i> hallPoints)
{
    hallPoints_ = hallPoints;
}

void Room::SetHallPoint(sf::Vector2i hallPoint)
{
    hallPoints_.push_back(hallPoint);
}

std::vector<sf::Vector2i> Room::GetHallPoints() const
{
    return hallPoints_;
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

        int x = (rand() % (roomWidth_ - 3)) + 1;
        int y = (rand() % (roomHeight_ - 4)) + 2;
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
    int tilemap[roomWidth_ * roomHeight_];
    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomWidth_; x++)
        {
            //tileMapKeys_.push_back(LP::SetSprite(tile_map, sf::Vector2f((x + position_.x) * CellSize, (y + position_.y) * CellSize), CellSize, CellSize, roomMap_[x][y]));
            tilemap[x + y * roomWidth_] = roomMap_[x][y];
        }
    }
    roomTileMap_ = LP::SetTileMap(tile_map, sf::Vector2u(32, 32), tilemap, sf::Vector2f(position_.x * CellSize, position_.y * CellSize), roomWidth_, roomHeight_);
}

void Room::SetRoomObjectMap(const std::string& roomObjectDataLocation)
{
    std::ifstream mapData(roomObjectDataLocation);
    char dummy;
    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomWidth_; x++)
        {
            mapData >> roomObjectMap_[x][y];
            if (roomObjectMap_[x][y] == 32) roomObjectMap_[x][y] = (rand() % 4) + 35; //random wall tiles
            if (roomObjectMap_[x][y] == 41) roomObjectMap_[x][y] = (rand() % 15) + 41; //random floor tiles
            if (x < roomWidth_ - 1) 
            {//removes "," 
                mapData >> dummy;
            }
        }
    }
    mapData.close();
}

void Room::SetRoomObjectMapNull()
{
    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomWidth_; x++)
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

        int x = (rand() % (roomWidth_ - 3)) + 1;
        int y = (rand() % (roomHeight_ - 4)) + 2;
        if (roomMap_[x][y] >= 40 && roomObjectMap_[x][y] == -1) 
        {
            done = true;
            roomObjectMap_[x][y] = 0;
        }
    }
}

void Room::SetEnemiesRand(int numOfEnemies)
{
    if (blockRandSpawn_) return;

    int done = 0;
    int failsafe = 0;
    while (done < numOfEnemies)
    {
        failsafe++;
        if (failsafe >= 100) return;

        int x = (rand() % (roomWidth_ - 3)) + 1;
        int y = (rand() % (roomHeight_ - 4)) + 2;
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
    int mapX = worldCoordinate.x  / CellSize - position_.x;
    int mapY = worldCoordinate.y  / CellSize - position_.y;

    if (mapX < 0 || mapX >= roomWidth_ || mapY < 0 || mapY >= roomHeight_)
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
    //for (auto i : tileMapKeys_) LP::DeleteSprite(i);
    LP::DeleteTileMap(roomTileMap_);
}