#include "Room3.h"

Room3::Room3(sf::Vector2i position, bool playerRoom, bool stairRoom)
{
    roomDataLocation_ = "./Resources/Map/Test/Factory_Room3.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 18;
    playerRoom_ = playerRoom;
    stairRoom_ = stairRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    SetHallPoint(sf::Vector2i(0, 4));
    SetHallPoint(sf::Vector2i(0, 13));
    SetHallPoint(sf::Vector2i(4, 17));
    SetHallPoint(sf::Vector2i(8, 4));
    SetHallPoint(sf::Vector2i(8, 13));

    SetRoomMap();
}