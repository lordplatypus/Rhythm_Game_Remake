#ifndef MAP_1_2_H_
#define MAP_1_2_H_
#include "../Map/MultiRoomMap.h"

class Map1_2 : public MultiRoomMap
{
public:
    Map1_2(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif