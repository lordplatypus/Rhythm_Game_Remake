#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "../Scene/Scene.h"
#include "Room.h"
#include "../Engine/Camera.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Enemy/GlobalEnemyManager.h"
#include "../Transition/TransitionManager.h"
#include "../Particle/ParticleManager.h"

class Map
{
public:
    Map();
    virtual ~Map();
    virtual void Draw();
    virtual std::vector<sf::IntRect> GetMapArea() const;
    virtual bool IsWall(sf::Vector2f worldCoordinate);

    void PlaceObjectsUsingObjectMap(std::vector<std::vector<int> > objectMap);
    void PlaceObjectsInRoom(sf::IntRect roomArea, std::vector<std::vector<int> > objectMap);

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
    GlobalEnemyManager* globalEnemyManager_{nullptr};
    TransitionManager* transitionManager_{nullptr};
    const int CellSize = 32;
    int mapWidth_ = 0;
    int mapHeight_ = 0;
};

#endif