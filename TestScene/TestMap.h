#ifndef TEST_MAP_H_
#define TEST_MAP_H_
#include "../Map/Map.h"

class TestMap : public Map
{
public:
    TestMap(Scene *scene, Camera* camera, PlayerManager* playerManager, LocalEnemyManager* localEnemyManager, TransitionManager* transitionManager, ParticleManager* particleManager);
    ~TestMap() override;
    void CreateMap() override;
    void DetailMap();
    void PlaceObjects() override;
    void Draw() override;
};

#endif