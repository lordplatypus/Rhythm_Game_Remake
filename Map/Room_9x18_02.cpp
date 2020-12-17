#include "Room_9x18_02.h"

Room_9x18_02::Room_9x18_02(sf::Vector2i position, bool blockRandSpawn, bool playerRoom)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_9x18_02.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 18;
    blockRandSpawn_ = blockRandSpawn;
    playerRoom_ = playerRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);

    SetHallPoint(sf::Vector2i(0, 4)); //W
    SetHallPoint(sf::Vector2i(0, 13)); //W
    SetHallPoint(sf::Vector2i(4, 17)); //S
    SetHallPoint(sf::Vector2i(8, 4)); //E
    SetHallPoint(sf::Vector2i(8, 13)); //E

    SetRoomMap();
    
    if (playerRoom_) SetPlayerRand();
    if (!blockRandSpawn_) SetEnemiesRand(rand() % 10 + 1);
}