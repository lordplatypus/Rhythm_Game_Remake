#include "Map1_3.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"
#include <fstream>
#include <cstdlib>

Map1_3::Map1_3(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{    
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    CreateMapWithRooms(9, "Lobby");
}