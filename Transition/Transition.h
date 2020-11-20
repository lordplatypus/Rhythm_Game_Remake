#ifndef TRANSITION_H_
#define TRANSITION_H_
#include "../Gameobjects/GameObject.h"
#include "TransitionManager.h"
#include "../Particle/ParticleManager.h"

class Transition : public GameObject
{
public:
    Transition(TransitionManager* tm, const std::string& transitionTo, const sf::Vector2f position, const bool locked, Scene* scene, ParticleManager* particleManager);
    virtual ~Transition();
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void ReactOnCollision(GameObject& other) override;

private:
    TransitionManager* tm_{nullptr};
    ParticleManager* particleManager_{nullptr};
    bool foundPlayer_{false};
    float count_{1.0f};
    int sprite_{0};
};

#endif