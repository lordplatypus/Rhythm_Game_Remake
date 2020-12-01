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
    for (int i = 0; i < tileMapKeys_.size(); i++)
    {
        LP::DrawSprite(tileMapKeys_[i]);
    }
}

void Room::SetRoomArea(int left, int top, int width, int height)
{
    roomArea_ = sf::IntRect(left, top, width, height);
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
    std::vector<int> resize(roomHeight_);
    roomMap_.resize(roomWidth_, resize);

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
    // std::ifstream mapData("./Resources/Map/Factory_Hall_Left_Main.csv");
    // for (int y = 2; y < 7; y++)
    // {
    //     mapData >> roomMap_[0][y];
    //     if (roomMap_[0][y] == 41) roomMap_[0][y] = (rand() % 15) + 41; //random floor tiles
    // }
    // mapData.close();

    roomMap_[position.x][position.y - 2] = 8;
    roomMap_[position.x][position.y - 1] = 32;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 2] = 4;
}

void Room::CreateRightHall(sf::Vector2i position)
{
    // std::ifstream mapData("./Resources/Map/Factory_Hall_Right_Main.csv");
    // for (int y = 2; y < 7; y++)
    // {
    //     mapData >> roomMap_[roomWidth_-1][y];
    //     if (roomMap_[roomWidth_-1][y] == 41) roomMap_[roomWidth_-1][y] = (rand() % 15) + 41; //random floor tiles
    // }
    // mapData.close();

    roomMap_[position.x][position.y - 2] = 7;
    roomMap_[position.x][position.y - 1] = 32;
    roomMap_[position.x][position.y] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 1] = (rand() % 15) + 41;
    roomMap_[position.x][position.y + 2] = 3;
}

void Room::CreateUpHall(sf::Vector2i position)
{
    // std::ifstream mapData("./Resources/Map/Factory_Hall_Top_Main.csv");
    // char dummy;
    // for (int y = 0; y < 2; y++)
    // {
    //     for (int x = 3; x < 7; x++)
    //     {
    //         mapData >> roomMap_[x][y];
    //         if (roomMap_[x][y] == 41) roomMap_[x][y] = (rand() % 15) + 41; //random floor tiles
    //         if (x < 6) 
    //         {//removes "," 
    //             mapData >> dummy;
    //         }
    //     }
    // }
    // mapData.close();
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
    // std::ifstream mapData("./Resources/Map/Factory_Hall_Bottom_Main.csv");
    // char dummy;
    // for (int x = 3; x < 7; x++)
    // {
    //     mapData >> roomMap_[x][roomHeight_-1];
    //     if (roomMap_[x][roomHeight_-1] == 41) roomMap_[x][roomHeight_-1] = (rand() % 15) + 41; //random floor tiles
    //     if (x < 6) 
    //     {//removes "," 
    //         mapData >> dummy;
    //     }
    // }
    // mapData.close();

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

void Room::SetRoomObjectMap()
{
    std::vector<int> resize(roomHeight_);
    roomObjectMap_.resize(roomWidth_, resize);

    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomHeight_; x++)
        {
            if (roomMap_[x][y] == 40) continue;
            else if (roomMap_[x][y] >= 100) continue;
            else if (roomMap_[x][y] < 40) 
            {
                roomObjectMap_[x][y] = -1;
                continue;
            }

            if (rand() % 10 == 0) roomObjectMap_[x][y] = rand() % 4 + 1;
            else roomObjectMap_[x][y] = -1;
        }
    }
}

std::vector<std::vector<int>> Room::GetRoomObjectMap() const
{
    return roomObjectMap_;
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

bool CheckForHallConnection(std::vector<sf::Vector2i> other)
{
    
}

void Room::SetTiles()
{
    for (int y = 0; y < roomHeight_; y++)
    {
        for (int x = 0; x < roomWidth_; x++)
        {
            tileMapKeys_.push_back(LP::SetSprite(tile_map, sf::Vector2f((x + position_.x) * CellSize, (y + position_.y) * CellSize), CellSize, CellSize, roomMap_[x][y]));
        }
    }
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

bool Room::PlayerRoom() const
{
    return playerRoom_;
}

bool Room::StairRoom() const
{
    return stairRoom_;
}

void Room::End()
{
    for (auto i : tileMapKeys_) LP::DeleteSprite(i);
}