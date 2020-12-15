#ifndef MORTAR_STRIKE_H_
#define MORTAR_STRIKE_H_
#include "Event.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"
#include "../Enemy/Generator.h"

class MortarStrike : public Event
{
public:
    MortarStrike(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, LocalEnemyManager* lem,ParticleManager* pm, Map* map);
    void Update(float delta_time, float beat_time) override;
    void EventTrigger() override;

private:
    void PlaceGenerator();
    void FireMortar();

private:
    PlayerManager* playerManager_{nullptr};
    ParticleManager* pm_{nullptr};
    Map* map_{nullptr};
    LocalEnemyManager* lem_{nullptr};
    const int CellSize = 32;
    bool generatorDestroyed_{false};

    float windowOfInput_{0.0f};
    bool input_{false};
    int fireCountDown_{10};

    Generator* generator_{nullptr};
};

#endif