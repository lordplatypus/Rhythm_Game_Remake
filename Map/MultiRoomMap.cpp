#include "MultiRoomMap.h"
//Rooms
#include "../Map/Room1.h"
#include "../Map/Room2.h"
#include "../Map/Room3.h"
#include "../Map/Junkyard.h"

MultiRoomMap::MultiRoomMap()
{}

MultiRoomMap::~MultiRoomMap()
{
    for (auto room : rooms_) delete room;
}

void MultiRoomMap::Draw()
{
    for (auto i : rooms_)
    {
        i->Draw();
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
}

void MultiRoomMap::CreateMapWithRooms(int numOfRooms, const std::string& transitionTo)
{
    SetRooms(numOfRooms);
    SetHalls();
    SetTransition(transitionTo);
    BuildMapBlueprint();
}

void MultiRoomMap::SetRooms(int numOfRooms)
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
                    prevRoom = rooms_[rand() % (rooms_.size() - 1)];
                    currentRoom->SetRoomPosition(prevRoom->GetRoomPosition());
                }
            }
        }
        prevRoom = currentRoom;
    }
}

Room* MultiRoomMap::SetGetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum)
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


//MOVE TO ROOM.H
void MultiRoomMap::SetTransition(const std::string& transitionTo)
{
    rooms_.back()->SetStairRand(transitionManager_->GetSceneID(transitionTo));
}

void MultiRoomMap::BuildMapBlueprint()
{
    for (auto i : rooms_)
    {
        i->SetTiles();
        PlaceObjectsInRoom(i->GetRoomArea(), i->GetRoomObjectMap());
    }
}