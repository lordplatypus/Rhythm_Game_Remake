#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "../Scene/Scene.h"
#include "Room.h"
#include "../Engine/Camera.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Transition/TransitionManager.h"
#include "../Particle/ParticleManager.h"

class Map
{
public:
    Map();
    virtual ~Map();
    virtual void Draw();
    virtual void CreateMap();
    virtual void PlaceObjects();
    virtual void PlaceObjectsUsingObjectMap(std::vector<std::vector<int> > objectMap);
    virtual void CreateMapWithRooms(int numOfRooms, const std::string& transitionTo);

private:
    void SetRooms(int numOfRooms);
    Room* SetGetRandRoom(sf::Vector2i position, int roomBuildOrderNum, int maxRoomNum);
    void SetHalls();
    void SetTransition(const std::string& transitionTo);
    void BuildMapBlueprint();
    void PlaceObjectsInRoom(sf::IntRect roomArea, std::vector<std::vector<int> > objectMap); 

public:
    virtual int GetLocation(sf::Vector2f worldCoordinate);
    virtual bool IsWall(sf::Vector2f worldCoordinate);
    virtual bool IsStair(sf::Vector2f worldCoordinate);

private:
    void PlaceEnemy(int num, sf::Vector2f position);
    void PlaceItem(int num, sf::Vector2f position);
    void PlaceTransition(int num, sf::Vector2f position);

protected:
    Scene* scene_{nullptr};
    Camera* camera_{nullptr};
    PlayerManager* playerManager_{nullptr};
    ParticleManager* particleManager_{nullptr};
    LocalEnemyManager* localEnemyManager_{nullptr};
    TransitionManager* transitionManager_{nullptr};
    const int CellSize = 32;
    int MapSize_ = 30;
    int mapWidth_ = 0;
    int mapHeight_ = 0;
    
    //Regular Map
    std::vector<std::vector<int> > map_;
    std::vector<std::vector<int> > objectMap_;
    std::vector<int> tileMapKeys_;

    //For making a map with rooms
    std::vector<Room*> rooms_;
};

#endif