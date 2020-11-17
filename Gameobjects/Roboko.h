#ifndef ROBOKO_H_
#define ROBOKO_H_
#include "GameObject.h"
#include "../Managers/PlayerManager.h"
#include "../Managers/TransitionManager.h"
#include "../Map/Map.h"
#include "../Engine/Camera.h"
#include "../UI/UIHeart.h"

class Roboko : public GameObject
{
public:
    Roboko(sf::Vector2f position, Scene *scene, Camera* camera, PlayerManager* pm, TransitionManager* transitionManager, Map* map);
    ~Roboko() override;
    void Update(float delta_time, float beat_time) override;
    void Draw() override;
    void DelayedDraw() override;
    void ReactOnCollision(GameObject& other) override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;
    void SetPerception(const float perception) override;
    float GetPerception() const override;

private:
    void InputHandle(float delta_time, float beat_time);
    void AnimationHandle(float delta_time, float beat_time);
    void UseSkill();
    void CheckMoveLocation();

private:
    Camera* camera_{nullptr};
    PlayerManager* playerManager_{nullptr};
    TransitionManager* transitionManager_{nullptr};
    Map* map_{nullptr};

    //sprite
    std::vector<int> sprites_;

    //Animation
    enum State {Normal, AttackLeft, AttackRight, AttackDown, AttackUp, Damage, CannonRise, CannonPowerUp, CannonShoot, CannonCoolDown};
    State state_ {Normal};
    bool flip_{false};
    float windowOfInput_{0.0f};
    float timeInbetweenFrames_{0.0f};
    int animCount_{0};
    float timer_{0.0f};

    //HP
    UIHeart* uiHeart_{nullptr};

    //movement
    const int CellSize{32};
    bool hasMoved_{false};
    bool stunned{false};

    //Atack
    int attackType_{-1};

    //Skill
    int skillCount{0};
    int prevAttackInput{-1};
    int cooldownBase{5};//stores the current num of destroyed enemies so that cooldown can be calculated
    //int cooldown{5};//num needed to use special again
};

#endif