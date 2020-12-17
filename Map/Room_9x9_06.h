#ifndef ROOM_9X9_06_H_
#define ROOM_9X9_06_H_
#include "Room.h"

class Room_9x9_06 : public Room
{
public:
    Room_9x9_06(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif