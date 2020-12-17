#include "Room_15x9_01.h"

Room_15x9_01::Room_15x9_01(sf::Vector2i position, bool blockRandSpawn, bool playerRoom)
{
    roomDataLocation_ = "./Resources/Map/Room/Factory_Room_15x9_01.csv";
    position_ = position;
    roomWidth_ = 15;
    roomHeight_ = 9;
    blockRandSpawn_ = blockRandSpawn;
    playerRoom_ = playerRoom;

    SetRoomArea(position_.x, position_.y, roomWidth_, roomHeight_);
    
    SetHallPoint(sf::Vector2i(0, 4)); //left anchor
    SetHallPoint(sf::Vector2i(4, 0)); //top anchor
    SetHallPoint(sf::Vector2i(7, 0)); //top anchor
    SetHallPoint(sf::Vector2i(10, 0)); //top anchor
    SetHallPoint(sf::Vector2i(4, 0)); //top anchor
    SetHallPoint(sf::Vector2i(14, 4)); //right anchor
    SetHallPoint(sf::Vector2i(4, 8)); //bottom anchor
    SetHallPoint(sf::Vector2i(7, 8)); //bottom anchor
    SetHallPoint(sf::Vector2i(10, 8)); //bottom anchor

    SetRoomMap();

    if (playerRoom_) SetPlayerRand();
    if (!blockRandSpawn_) SetEnemiesRand(rand() % 3);
}