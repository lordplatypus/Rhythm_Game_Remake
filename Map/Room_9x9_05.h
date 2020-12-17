#ifndef ROOM_9X9_05_H_
#define ROOM_9X9_05_H_
#include "Room.h"

class Room_9x9_05 : public Room
{
public:
    Room_9x9_05(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif