#include "Map1_3.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include <fstream>
#include <cstdlib>

Map1_3::Map1_3(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{    
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    globalEnemyManager_ = globalEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    CreateMapWithRooms(9, "Title");
}