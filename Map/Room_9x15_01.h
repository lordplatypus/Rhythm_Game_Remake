#ifndef ROOM_9X15_01_H_
#define ROOM_9X15_01_H_
#include "Room.h"

class Room_9x15_01 : public Room
{
public:
    Room_9x15_01(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif