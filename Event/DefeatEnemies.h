#ifndef DEFEAT_ENEMIES_H_
#define DEFEAT_ENEMIES_H_
#include "Event.h"
#include "../Enemy/LocalEnemyManager.h"

class DefeatEnemies : public Event
{
public:
    DefeatEnemies(const std::string& lockTarget, Camera* camera, TransitionManager* transitionManager, LocalEnemyManager* lem);

    void Update(float delta_time, float beat_time) override;

private:
    LocalEnemyManager* lem_{nullptr};
    int numToDefeat_{0};
    int defeatedNum_{0};
};

#endif