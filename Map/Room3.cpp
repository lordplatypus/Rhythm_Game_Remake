#include "Room3.h"

Room3::Room3(sf::Vector2i position, bool blockRandSpawn, bool playerRoom)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_03.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 18;
    blockRandSpawn_ = blockRandSpawn;
    playerRoom_ = playerRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    SetHallPoint(sf::Vector2i(0, 4));
    SetHallPoint(sf::Vector2i(0, 13));
    SetHallPoint(sf::Vector2i(4, 17));
    SetHallPoint(sf::Vector2i(8, 4));
    SetHallPoint(sf::Vector2i(8, 13));

    SetRoomMap();
    
    if (playerRoom_) SetPlayerRand();
    if (!blockRandSpawn_) SetEnemiesRand(rand() % 10 + 1);
}