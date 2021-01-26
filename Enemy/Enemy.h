#ifndef ENEMY_H_
#define ENEMY_H_
#include "../Gameobjects/GameObject.h"
#include "LocalEnemyManager.h"
#include "../UI/UIArrow.h"
#include "../Player/PlayerManager.h"
#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"

class Enemy : public GameObject
{
public:
    Enemy();
    virtual ~Enemy();
    virtual void AnimationHandle(float delta_time, float beat_time);
    virtual void TakeDamage(const int damage) override;
    void CheckMoveLocation();

    void SetPerception(const float perception) override;
    float GetPerception() const override;
    void SetInRangeOfPlayer(const bool inRangeOfPlayer) override;
    bool GetInRangeOfPlayer() const override;
    void DropMoney();
    int GetID() const override;

    void Kill() override;

protected:
    UIArrow* arrow_{nullptr};
    LocalEnemyManager* lem_{nullptr};
    EnemyData* ed_{nullptr};
    PlayerManager* playerManager_{nullptr};
    ParticleManager* pm_{nullptr};
    Map* map_{nullptr};

    bool inRangeOfPlayer_{false};
    int HP_{0};
    const int CellSize{32};

    //must be set within each enemy class
    std::vector<sf::Sprite> enemySprite_;
    //must be set within the enemy_ constructor
    int numOfBeatsBetweenAttacks_{0};
    int beatCount_{0};
    int animCount_{0};
    //The amount of micro sec inbetween animation frames
    float timeInbetweenFrames_{0};
    float timer_{0};
    bool flip_{false};
    float windowOfInput_{0};
};

#endif