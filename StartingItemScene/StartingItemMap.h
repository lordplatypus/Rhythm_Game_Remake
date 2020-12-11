#ifndef STARTING_ITEM_Map_H_
#define STARTING_ITEM_Map_H_
#include "../Map/SingleRoomMap.h"

class StartingItemMap : public SingleRoomMap
{
public:
    StartingItemMap(Scene *scene, Camera* camera, PlayerManager* playerManager, GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif