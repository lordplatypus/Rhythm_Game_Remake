#include "Room2.h"

Room2::Room2(sf::Vector2i position, bool blockRandSpawn, bool playerRoom)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_02.csv";
    position_ = position;
    roomWidth_ = 18;
    roomHeight_ = 9;
    blockRandSpawn_ = blockRandSpawn;
    playerRoom_ = playerRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    SetHallPoint(sf::Vector2i(0, 4));
    SetHallPoint(sf::Vector2i(4, 0));
    SetHallPoint(sf::Vector2i(13, 0));
    SetHallPoint(sf::Vector2i(17, 4));
    SetHallPoint(sf::Vector2i(4, 8));
    SetHallPoint(sf::Vector2i(13, 8));

    SetRoomMap();
    
    if (playerRoom_) SetPlayerRand();
    if (!blockRandSpawn_) SetEnemiesRand(rand() % 10 + 1);
}