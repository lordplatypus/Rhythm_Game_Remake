#ifndef INVISIBLE_ENEMIES_H_
#define INVISIBLE_ENEMIES_H_
#include "Event.h"
#include "../Map/Map.h"
#include "../Particle/ParticleManager.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Enemy/Generator.h"

class InvisibleEnemies : public Event
{
public:
    InvisibleEnemies(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, ParticleManager* pm, Map* map, LocalEnemyManager* lem);
    void Update(float delta_time, float beat_time) override;
    void EventTrigger() override;

private:
    void PlaceGenerator();

private:
    PlayerManager* playerManager_{nullptr};
    ParticleManager* pm_{nullptr};
    Map* map_{nullptr};
    LocalEnemyManager* lem_{nullptr};
    const int CellSize = 32;
    bool generatorDestroyed_{false};
    Generator* generator_{nullptr};
};

#endif