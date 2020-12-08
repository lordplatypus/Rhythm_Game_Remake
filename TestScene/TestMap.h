#ifndef TEST_MAP_H_
#define TEST_MAP_H_
#include "../Map/SingleRoomMap.h"

class TestMap : public SingleRoomMap
{
public:
    TestMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif