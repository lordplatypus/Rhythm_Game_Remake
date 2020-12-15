#include <fstream>
#include "StartingItemMap.h"
#include "../Engine/LP.h"
#include "../Assets/ID.h"


StartingItemMap::StartingItemMap(Scene *scene, Camera* camera, PlayerManager* playerManager, GlobalEnemyManager* globalEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager)
{
    scene_ = scene;
    camera_ = camera;
    playerManager_ = playerManager;
    globalEnemyManager_ = globalEnemyManager;
    transitionManager_ = transitionManager;
    particleManager_ = particleManager;

    // SetMapArea(20, 20);
    // LoadTilesFromCSC("./Resources/Map/StartingItemRoom/StartingItemRoom_Main.csv");
    // LoadObjectsFromCSC("./Resources/Map/StartingItemRoom/StartingItemRoom_Object.csv");
    SetMapArea(19, 20);
    LoadTilesFromCSC("./Resources/Map/ItemShowcase/Item_Showcase_Main.csv");
    LoadObjectsFromCSC("./Resources/Map/ItemShowcase/Item_Showcase_Object.csv");
}