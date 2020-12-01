#include "Room1.h"

Room1::Room1(sf::Vector2i position, bool playerRoom, bool stairRoom)
{
    roomDataLocation_ = "./Resources/Map/Test/Factory_Room1.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 9;
    playerRoom_ = playerRoom;
    stairRoom_ = stairRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    //SetHallPoint(sf::Vector2i(0, 0)); //left anchor
    //SetHallPoint(sf::Vector2i(0, 10)); //top anchor
    //SetHallPoint(sf::Vector2i(10, 10)); //right anchor
    //SetHallPoint(sf::Vector2i(10, 0)); //bottom anchor
    SetHallPoint(sf::Vector2i(0, 4)); //left anchor
    SetHallPoint(sf::Vector2i(4, 0)); //top anchor
    SetHallPoint(sf::Vector2i(8, 4)); //right anchor
    SetHallPoint(sf::Vector2i(4, 8)); //bottom anchor

    SetRoomMap();
}