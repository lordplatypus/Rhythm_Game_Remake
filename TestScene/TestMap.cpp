#include <fstream>
#include "TestMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"

TestMap::TestMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    localEnemyManager_ = localEnemyManager;
    globalEnemyManager_ = globalEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;
    SetMapArea(10, 10);

    LoadTilesFromCSC("./Resources/Map/Test_Map_Factory_Main.csv");
    LoadDetailsFromCSC("./Resources/Map/Test_Map_Factory_Detail.csv");
    LoadObjectsFromCSC("./Resources/Map/Test_Map_Factory_Object.csv");
}