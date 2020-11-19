#ifndef TEST_SCENE_H_
#define TEST_SCENE_H_
#include "../Scene/Scene.h"
#include "../Gameobjects/GameObjectManager.h"
#include "../Engine/Game.h"
#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"

class TestScene : public Scene
{
public:
    TestScene(Game* game);
    ~TestScene() override;
    void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    void End() override;

private:
    std::string transitionTo_{""};

    GameObjectManager gameObjects_;
    ParticleManager pm_;
    Map* map_ {nullptr};
    Game* game_ {nullptr};

    bool saveState_{false};
};

#endif