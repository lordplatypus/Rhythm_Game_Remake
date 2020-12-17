#ifndef ROOM_15X9_01_H_
#define ROOM_15X9_01_H_
#include "Room.h"

class Room_15x9_01 : public Room
{
public:
    Room_15x9_01(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif