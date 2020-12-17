#ifndef ROOM_9x9_03_H_
#define ROOM_9x9_03_H_
#include "Room.h"

class Room_9x9_03 : public Room
{
public:
    Room_9x9_03(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif