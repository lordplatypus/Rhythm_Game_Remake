#ifndef ROOM_9X9_04_H_
#define ROOM_9X9_04_H_
#include "Room.h"

class Room_9x9_04 : public Room
{
public:
    Room_9x9_04(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif