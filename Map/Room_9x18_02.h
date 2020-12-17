#ifndef ROOM_9X18_02_H_
#define ROOM_9X18_02_H_
#include "Room.h"

class Room_9x18_02 : public Room
{
public:
    Room_9x18_02(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif