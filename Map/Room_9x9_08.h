#ifndef ROOM_9X9_08_H_
#define ROOM_9X9_08_H_
#include "Room.h"

class Room_9x9_08 : public Room
{
public:
    Room_9x9_08(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif