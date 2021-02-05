#ifndef FIND_KEYS_H_
#define FIND_KEYS_H_
#include "Event.h"
#include "../Map/Map.h"
#include "../Particle/ParticleManager.h"

class FindKeys : public Event
{
public:
    FindKeys(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, PlayerManager* playerManager, Scene* scene, ParticleManager* pm, Map* map, bool setKey = false, sf::Vector2f keyPosition = sf::Vector2f(0.0f, 0.0f));
    void Update(float delta_time, float beat_time) override;
    void PickUpKey();

private:
    void PlaceKeys();

private:
    PlayerManager* playerManager_{nullptr};
    ParticleManager* pm_{nullptr};
    Map* map_{nullptr};
    const int CellSize = 32;
    int keyCounter_{0};
};

#endif