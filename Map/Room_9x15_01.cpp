#include "Room_9x15_01.h"

Room_9x15_01::Room_9x15_01(sf::Vector2i position, bool blockRandSpawn, bool playerRoom)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_9x15_01.csv";
    position_ = position;
    roomWidth_ = 9;
    roomHeight_ = 15;
    blockRandSpawn_ = blockRandSpawn;
    playerRoom_ = playerRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);
    
    SetHallPoint(sf::Vector2i(0, 4)); //left anchor
    SetHallPoint(sf::Vector2i(0, 7)); //left anchor
    SetHallPoint(sf::Vector2i(0, 11)); //left anchor
    SetHallPoint(sf::Vector2i(4, 0)); //top anchor
    SetHallPoint(sf::Vector2i(8, 4)); //right anchor
    SetHallPoint(sf::Vector2i(8, 7)); //left anchor
    SetHallPoint(sf::Vector2i(8, 11)); //left anchor
    SetHallPoint(sf::Vector2i(4, 14)); //bottom anchor

    SetRoomMap();

    if (playerRoom_) SetPlayerRand();
    if (!blockRandSpawn_) SetEnemiesRand(rand() % 3);
}