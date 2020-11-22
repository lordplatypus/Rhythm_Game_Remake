#ifndef SPAWNER_H_
#define SPAWNER_H_
#include "Event.h"
#include "../Enemy/Enemy5.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Player/PlayerManager.h"
#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"

class Spawner : public Event
{
public:
    Spawner(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, Scene* scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);

    void Update(float delta_time, float beat_time) override;

private:
    Enemy5* spawner_{nullptr};

    bool done_{false};
};

#endif