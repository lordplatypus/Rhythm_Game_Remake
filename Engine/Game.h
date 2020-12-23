#ifndef GAME_H_
#define GAME_H_
#include <unordered_map>
#include "../Scene/Scene.h"
#include "../Assets/LoadAssets.h"
#include "Camera.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/GlobalEnemyManager.h"
#include "../Transition/TransitionManager.h"

class Game
{
public:
    Game(Camera* camera);
    ~Game();
    //Update Game
    void Update(float delta_time, float beat_time);
    //Draw Game
    void Draw(const sf::RenderWindow& render_window);
    //Add a Scene to the scene map
    void AddScene(const std::string& name, Scene* scene);
    //Switch to a different scene
    void ChangeScene(const std::string& newScene);
    //End a scene
    void EndScene();
    Camera* GetCamera();
    PlayerManager* GetPlayerManager();
    GlobalEnemyManager* GetGlobalEnemyManager();
    TransitionManager* GetTransitionManager();
    //Called on program shutdown, delete scenes here
    void Clear();

    Game(const Game& other) = delete;
    Game& operator = (const Game& other) = delete;

private:
    //Stores scenes with string key
    std::unordered_map<std::string, Scene*> scenes_;
    //Current loaded scene
    Scene* scene_ {nullptr};
    Camera* camera_{nullptr};
    PlayerManager* playerManager_{nullptr};
    GlobalEnemyManager gem_;
    TransitionManager transitionManager_;
    //load assets
    LoadAssets loadAssets_;

    //Win status
    bool win_{false};
};

#endif