#ifndef ROOM_2_H_
#define ROOM_2_H_
#include "Room.h"

class Room2 : public Room
{
public:
    Room2(sf::Vector2i position, bool playerRoom = false, bool stairRoom = false);
};

#endif