#include "Junkyard.h"

Junkyard::Junkyard(sf::Vector2i position)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_Junkyard.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 14;
    blockRandSpawn_ = true;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);
    
    SetHallPoint(sf::Vector2i(0, 9));
    SetHallPoint(sf::Vector2i(4, 13));
    SetHallPoint(sf::Vector2i(8, 9));

    SetRoomMap();

    PlaceItem(sf::Vector2i(2, 7));
    PlaceItem(sf::Vector2i(4, 7));
    PlaceItem(sf::Vector2i(6, 7));
}

void Junkyard::PlaceItem(sf::Vector2i position)
{
    bool done = false;
    int failsafe = 0;
    while(!done)
    {
        done = true;
        int randItemID = rand() % 8 + 101;
        for (auto i : placedItems_)
        {
            if (i == randItemID) done = false;
        }
        if (done)
        {
            SetObject(position, randItemID);
            placedItems_.push_back(randItemID);
        }

        failsafe++;
        if (failsafe >= 100) done = true;
    }
}