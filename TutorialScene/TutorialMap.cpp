#include <fstream>
#include "TutorialMap.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"


TutorialMap::TutorialMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager,  GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    globalEnemyManager_ = globalEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;
    SetMapArea(28, 8);

    LoadTilesFromCSC("./Resources/Map/TutorialMap/Factory_Tutorial_Main.csv");
    LoadObjectsFromCSC("./Resources/Map/TutorialMap/Factory_Tutorial_Object.csv");
}