#ifndef MULTI_ROOM_MAP_H_
#define MULTI_ROOM_MAP_H_
#include "Map.h"
#include "Room.h"

class MultiRoomMap : public Map
{
public:
    MultiRoomMap(const int numOfRooms, const std::string& transitionTo, Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager,  GlobalEnemyManager* globalEnemyManager,TransitionManager* transitionManager, ParticleManager* particleManager);
    ~MultiRoomMap();
    virtual void Draw(sf::RenderWindow& render_window) override;
    std::vector<sf::IntRect> GetMapArea() const override;
    virtual bool IsWall(sf::Vector2f worldCoordinate) override;

private:
    //step 1: place rooms
    void SetRoomPositions(int numOfRooms);
    Room* GetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum);

    //step 2: generate maps for each room
    void SetRoomTileMap();
    void SetRoomHalls();

    //step 3: place objects in rooms
    void SetRoomObjectMap();
    void SetRoomObjects();

    //step 4: create sprites for each room tilemap
    void SetRoomTileMapSprite();

private:
    int numOfRooms_{0};
    std::string transitionTo_{""};

    std::vector<Room*> rooms_;
};

#endif