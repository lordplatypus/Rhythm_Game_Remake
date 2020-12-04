#ifndef JUNKYARD_H_
#define JUNKYARD_H_
#include "Room.h"

class Junkyard : public Room
{
public:
    Junkyard(sf::Vector2i position);

private:
    void PlaceItem(sf::Vector2i position);

private:
    std::vector<int> placedItems_;
};

#endif