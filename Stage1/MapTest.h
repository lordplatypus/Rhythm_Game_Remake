#ifndef MAP_Test_H_
#define MAP_Test_H_
#include "../Map/MultiRoomMap.h"

class MapTest : public MultiRoomMap
{
public:
    MapTest(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif