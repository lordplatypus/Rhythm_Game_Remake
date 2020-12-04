#ifndef ROOM_1_H_
#define ROOM_1_H_
#include "Room.h"

class Room1 : public Room
{
public:
    Room1(sf::Vector2i position, bool blockRandSpawn = false, bool playerRoom = false);
};

#endif