#ifndef LOBBY_SCENE_H_
#define LOBBY_SCENE_H_
#include <vector>
#include "../Scene/Scene.h"
#include "../Gameobjects/GameObjectManager.h"
#include "../Engine/Game.h"
#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"

class LobbyScene : public Scene
{
public:
    LobbyScene(Game* game);
    ~LobbyScene() override;
    virtual void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    virtual void End() override;

private:
    const int CellSize{32};
    std::string transitionTo_{""};

    GameObjectManager gameObjects_;
    ParticleManager pm_;
    Map* map_ {nullptr};
    Game* game_ {nullptr};
};

#endif