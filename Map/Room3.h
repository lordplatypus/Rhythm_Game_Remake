#ifndef ROOM_3_H_
#define ROOM_3_H_
#include "Room.h"

class Room3 : public Room
{
public:
    Room3(sf::Vector2i position, bool playerRoom = false, bool stairRoom = false);
};

#endif