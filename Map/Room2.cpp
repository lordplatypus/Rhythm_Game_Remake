#include "Room2.h"

Room2::Room2(sf::Vector2i position, bool playerRoom, bool stairRoom)
{
    roomDataLocation_ = "./Resources/Map/Test/Factory_Room2.csv";
    position_ = position;
    roomWidth_ = 18;
    roomHeight_ = 9;
    playerRoom_ = playerRoom;
    stairRoom_ = stairRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    SetHallPoint(sf::Vector2i(0, 4));
    SetHallPoint(sf::Vector2i(4, 0));
    SetHallPoint(sf::Vector2i(13, 0));
    SetHallPoint(sf::Vector2i(17, 4));
    SetHallPoint(sf::Vector2i(4, 8));
    SetHallPoint(sf::Vector2i(17, 8));

    SetRoomMap();
}