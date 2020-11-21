#ifndef STAGE_1_1_H_
#define STAGE_1_1_H_
#include "../Scene/Scene.h"
#include "../Gameobjects/GameObjectManager.h"
#include "../Engine/Game.h"
#include "../Particle/ParticleManager.h"
#include "../Enemy/LocalEnemyManager.h"
#include "../Map/Map.h"

class Stage1_1 : public Scene
{
public:
    Stage1_1(Game* game);
    ~Stage1_1() override;
    virtual void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    void End() override;

private:
    GameObjectManager gameObjects_;
    ParticleManager pm_;
    Map* map_ {nullptr};
    Game* game_ {nullptr};
    LocalEnemyManager* lem_{nullptr};

    std::string transitionTo_{""};
    bool saveState_{false};
};

#endif