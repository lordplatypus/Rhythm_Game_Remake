#include "MultiRoomMap.h"
//Rooms
#include "../Map/Junkyard.h"
#include "../Map/Room_9x9_01.h"
#include "../Map/Room_9x9_02.h"
#include "../Map/Room_9x9_03.h"
#include "../Map/Room_9x9_04.h"
#include "../Map/Room_9x9_05.h"
#include "../Map/Room_9x9_06.h"
#include "../Map/Room_9x9_07.h"
#include "../Map/Room_9x9_08.h"
#include "../Map/Room_9x15_01.h"
#include "../Map/Room_9x15_02.h"
#include "../Map/Room_9x18_01.h"
#include "../Map/Room_9x18_02.h"
#include "../Map/Room_15x9_01.h"
#include "../Map/Room_18x9_01.h"

MultiRoomMap::MultiRoomMap()
{}

MultiRoomMap::~MultiRoomMap()
{
    for (auto room : rooms_) delete room;
}

void MultiRoomMap::Draw(sf::RenderWindow& render_window)
{
    for (auto i : rooms_)
    {
        if (camera_->GetCameraRect().intersects(i->GetRoomAreaWorldCoordinates()))
            i->Draw(render_window);
    }
}

std::vector<sf::IntRect> MultiRoomMap::GetMapArea() const
{
    std::vector<sf::IntRect> temp;
    for (auto room : rooms_)
    {
        temp.push_back(room->GetRoomArea());
    }
    return temp;
}

bool MultiRoomMap::IsWall(sf::Vector2f worldCoordinate)
{
    for (auto i : rooms_)
    {
        if (i->GetRoomArea().contains(sf::Vector2i(worldCoordinate.x / CellSize, worldCoordinate.y / CellSize))) return i->IsWall(sf::Vector2i(worldCoordinate.x, worldCoordinate.y)); 
    }
    return true;
}

void MultiRoomMap::CreateMapWithRooms(int numOfRooms, const std::string& transitionTo)
{
    transitionTo_ = transitionTo;
    SetRooms(numOfRooms);
    SetHalls();
    BuildMapBlueprint();
}

void MultiRoomMap::SetRooms(int numOfRooms)
{
    sf::Vector2i currentPosition(0, 0); //starting position is always (0, 0)
    RoomData* prevRoom = SetGetRandRoom(currentPosition, 0, numOfRooms); //creat first room
    rooms_.push_back(new Room(prevRoom));

    for (int i = 1; i < numOfRooms; i++)
    {
        int temp = rand() % 4;
        RoomData* currentRoom = SetGetRandRoom(currentPosition, i, numOfRooms);
        bool done = false;
        int changeRoom = 0;
        while (!done)
        {
            changeRoom++;
            if (changeRoom >= 10)
            {//if the program fails to place a room 10 times, try a different room
                changeRoom = 0;
                //rooms_.pop_back();
                delete currentRoom;
                currentRoom = SetGetRandRoom(currentPosition, i, numOfRooms);
            }

            currentPosition = prevRoom->GetPosition();

            sf::Vector2i hallPoint = prevRoom->hallPoints_[rand() % prevRoom->hallPoints_.size()] + prevRoom->GetPosition();

            if (hallPoint.x == prevRoom->roomArea_.left)//left
            {
                currentPosition = sf::Vector2i(hallPoint.x - currentRoom->roomArea_.width, hallPoint.y - 4);
                hallPoint.x--; //makes the calc in the for loop easier
                for (auto i : currentRoom->hallPoints_)
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.x == prevRoom->roomArea_.left + prevRoom->roomArea_.width - 1)//right
            {
                hallPoint.x++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x, hallPoint.y - 4);
                for (auto i : currentRoom->hallPoints_)
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->roomArea_.top)//top
            {
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y - currentRoom->roomArea_.height);
                hallPoint.y--; //makes the calc in the for loop easier
                for (auto i : currentRoom->hallPoints_)
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            else if (hallPoint.y == prevRoom->roomArea_.top + prevRoom->roomArea_.height - 1)//bottom
            {
                hallPoint.y++; //makes the calc in the for loop easier && puts the currentPosition in the right place
                currentPosition = sf::Vector2i(hallPoint.x - 4, hallPoint.y);
                for (auto i : currentRoom->hallPoints_)
                {
                    if (hallPoint == i + currentPosition) 
                    {
                        done = true; //2 hall points match up
                    }
                }
            }
            if (!done) continue;

            currentRoom->SetPosition(currentPosition);
            for (int i = 0; i < rooms_.size() - 1; i++)
            {
                if (currentRoom->roomArea_.intersects(rooms_[i]->GetRoomData()->roomArea_))
                {
                    done = false;
                    prevRoom = rooms_[rand() % (rooms_.size() - 1)]->GetRoomData();
                    currentRoom->SetPosition(prevRoom->GetPosition());
                }
            }
        }
        //Succeded in placing a room
        rooms_.push_back(new Room(currentRoom)); //add the new room to the vector of rooms
        prevRoom = currentRoom; //set up the new starting position for the next room
    }
}

RoomData* MultiRoomMap::SetGetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum)
{
    RoomData* roomData;
    std::string roomDataLocation = "";
    sf::IntRect roomArea;
    std::vector<sf::Vector2i> hallPoints;
    int randomEnemyCount = rand() % 3;

    if (roomBuildOrderNum == 0)
    {
        // room = new Room_9x9_01(position, true, true);
        // rooms_.push_back(room);
        // return room;
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        roomData = new RoomData(roomDataLocation, roomArea, hallPoints, 0, true, false, true);
        return roomData;
    }

    int randRoom = rand() % 15;
    switch (randRoom)
    {
        case 0:
        if (roomBuildOrderNum != 0 && roomBuildOrderNum != maxRoomNum - 1) 
        {
            roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_01.csv";
            roomArea = sf::IntRect(position.x, position.y, 9, 9);
            hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
            hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
            hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
            hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
            break;
        }
        roomDataLocation = "./Resources/Map/Room/Factory_Room_Junkyard.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 1:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 2:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_02.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 3:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_03.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 4:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_04.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 5:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_05.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        break;

        case 6:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_06.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(4, 0)); //top anchor
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        break;

        case 7:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_07.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(8, 4)); //right anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 8:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x9_08.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 9);
        hallPoints.push_back(sf::Vector2i(0, 4)); //left anchor
        hallPoints.push_back(sf::Vector2i(4, 8)); //bottom anchor
        break;

        case 9:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x15_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 15);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(0, 7));
        hallPoints.push_back(sf::Vector2i(0, 11));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(8, 4));
        hallPoints.push_back(sf::Vector2i(8, 7));
        hallPoints.push_back(sf::Vector2i(8, 11));
        hallPoints.push_back(sf::Vector2i(4, 14));
        break;

        case 10:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x15_02.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 15);
        hallPoints.push_back(sf::Vector2i(0, 7));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(8, 7));
        hallPoints.push_back(sf::Vector2i(4, 14));
        break;

        case 11:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x18_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 18);
        hallPoints.push_back(sf::Vector2i(4, 0)); //N
        hallPoints.push_back(sf::Vector2i(0, 4)); //W
        hallPoints.push_back(sf::Vector2i(0, 13)); //W
        hallPoints.push_back(sf::Vector2i(4, 17)); //S
        hallPoints.push_back(sf::Vector2i(8, 4)); //E
        hallPoints.push_back(sf::Vector2i(8, 13)); //E
        randomEnemyCount = rand() % 10 + 1;
        break;

        case 12:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_9x18_02.csv";
        roomArea = sf::IntRect(position.x, position.y, 9, 18);
        hallPoints.push_back(sf::Vector2i(0, 4)); //W
        hallPoints.push_back(sf::Vector2i(0, 13)); //W
        hallPoints.push_back(sf::Vector2i(4, 17)); //S
        hallPoints.push_back(sf::Vector2i(8, 4)); //E
        hallPoints.push_back(sf::Vector2i(8, 13)); //E
        randomEnemyCount = rand() % 10 + 1;
        break;

        case 13:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_15x9_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 15, 9);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(7, 0));
        hallPoints.push_back(sf::Vector2i(10, 0));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(14, 4));
        hallPoints.push_back(sf::Vector2i(4, 8));
        hallPoints.push_back(sf::Vector2i(7, 8));
        hallPoints.push_back(sf::Vector2i(10, 8));
        break;

        case 14:
        roomDataLocation = "./Resources/Map/Room/Factory_Room_18x9_01.csv";
        roomArea = sf::IntRect(position.x, position.y, 18, 9);
        hallPoints.push_back(sf::Vector2i(0, 4));
        hallPoints.push_back(sf::Vector2i(4, 0));
        hallPoints.push_back(sf::Vector2i(13, 0));
        hallPoints.push_back(sf::Vector2i(17, 4));
        hallPoints.push_back(sf::Vector2i(4, 8));
        hallPoints.push_back(sf::Vector2i(13, 8));
        randomEnemyCount = rand() % 10 + 1;
        break;

        default:
        break;
    }

    roomData = new RoomData(roomDataLocation, roomArea, hallPoints, randomEnemyCount);
    if (roomBuildOrderNum == maxRoomNum - 1) 
    {
        roomData->transitionID_ = transitionManager_->GetSceneID(transitionTo_);
        roomData->stairRoom_ = true;
    }
    return roomData;

    // rooms_.push_back(room);
    // return room;
}

void MultiRoomMap::SetHalls()
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

void MultiRoomMap::BuildMapBlueprint()
{
    for (auto i : rooms_)
    {
        i->SetTiles();
        PlaceObjectsInRoom(i->GetRoomArea(), i->GetRoomObjectMap());
    }
}