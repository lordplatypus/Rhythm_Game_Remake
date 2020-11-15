#ifndef SCENE_TITLE_H_
#define SCENE_TITLE_H_
#include <vector>
#include "../Scene/Scene.h"
#include "../Engine/Game.h"
#include "../Map/Map.h"
#include "../Particle/ParticleManager.h"

class TitleScene : public Scene
{
public:
    TitleScene(Game* game);
    ~TitleScene() override;
    virtual void Init() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void AddGameObject(GameObject* gameObject) override;
    GameObject* FindGameObject(const std::string& string, const bool byTag = true, const bool byID = false) override;
    void ChangeGameObjectOrder(const std::string& name, const std::string& newPos) override;
    void ChangeScene(const std::string& sceneName) override;
    void End() override;

private:
    void MovementHandle();
    void AnimationHandle(float delta_time, float beat_time);

private:
    Game* game_ {nullptr};
    Map* map_{nullptr};
    ParticleManager pm_;

    int infoText;
    int background;

    //Char
    //animation
    enum State {Normal, Damage};
    State state_ {Normal};
    bool flip_ {false};
    std::vector<int> playerSprite_;
    std::vector<int> playerSprite2_;
    int animCount_ = 0;
    float timeInbetweenFrames_;
    bool oncePerBeat = false;
    int timeOfBeatinMS = 0;
    int framesInOneAnimCycle;

    float timer_{0};
    int endingFrame_{0};
    float windowOfInput_{0};
    //movement
    sf::Vector2f position_{0.0f, 0.0f};
    sf::Vector2f velocity_{0.0f, 0.0f};
    sf::Vector2f prevPosition{0.0f, 0.0f};
    const int CellSize {32};
};

#endif