#ifndef MULTI_ROOM_MAP_H_
#define MULTI_ROOM_MAP_H_
#include "Map.h"
#include "Room.h"

class MultiRoomMap : public Map
{
public:
    MultiRoomMap();
    ~MultiRoomMap();
    virtual void Draw(sf::RenderWindow& render_window) override;
    std::vector<sf::IntRect> GetMapArea() const override;
    virtual bool IsWall(sf::Vector2f worldCoordinate) override;
    virtual void CreateMapWithRooms(int numOfRooms, const std::string& transitionTo);

private:
    void SetRooms(int numOfRooms);
    RoomData* SetGetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum);
    void SetHalls();
    void BuildMapBlueprint();

private:
    std::vector<Room*> rooms_;
    std::string transitionTo_{""};
};

#endif