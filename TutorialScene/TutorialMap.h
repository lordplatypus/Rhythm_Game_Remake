#ifndef TUTORIAL_MAP_H_
#define TUTORIAL_MAP_H_
#include "../Map/SingleRoomMap.h"

class TutorialMap : public SingleRoomMap
{
public:
    TutorialMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager,  GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
};

#endif