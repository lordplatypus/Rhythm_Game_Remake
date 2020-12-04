#ifndef MAP_1_1_H_
#define MAP_1_1_H_
#include "../Map/MultiRoomMap.h"

class Map1_1 : public MultiRoomMap
{
public:
    Map1_1(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif