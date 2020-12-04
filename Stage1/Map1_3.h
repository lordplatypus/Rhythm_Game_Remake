#ifndef MAP_1_3_H_
#define MAP_1_3_H_
#include "../Map/MultiRoomMap.h"

class Map1_3 : public MultiRoomMap
{
public:
    Map1_3(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif