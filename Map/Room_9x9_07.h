#ifndef ROOM_9X9_07_H_
#define ROOM_9X9_07_H_
#include "Room.h"

class Room_9x9_07 : public Room
{
public:
    Room_9x9_07(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif