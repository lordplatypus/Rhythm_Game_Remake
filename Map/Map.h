#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "../Scene/Scene.h"
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
    virtual void CreateMap();
    virtual void PlaceObjects();
    virtual void PlaceObjectsUsingObjectMap(std::vector<std::vector<int> > objectMap);
    virtual void Draw();
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
    
    std::vector<std::vector<int> > map_;
    std::vector<std::vector<int> > objectMap_;
    std::vector<int> tileMapKeys_;
};

#endif