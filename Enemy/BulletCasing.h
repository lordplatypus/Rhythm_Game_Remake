#ifndef BULLET_CASING_H_
#define BULLET_CASING_H_
#include <vector>
#include "../Gameobjects/GameObject.h"
//#include "../Particle/ParticleManager.h"
#include "../Map/Map.h"

class BulletCasing : public GameObject
{
public:
    BulletCasing(sf::Vector2f position, bool fliped, Scene *scene, ParticleManager* pm, Map* map);
    ~BulletCasing() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;
    void ReactInRange(GameObject& other) override;
    void ReactNotInRange(GameObject& other) override;
    //Check location
    void CheckMoveLocation();

private:
    ParticleManager* pm_{nullptr};
    Map* map_{nullptr};

    float lifespan_{0.0f};
    float age_{0.0f};
    float vx_{0.0f};
    float vy_{0.0f};
    float forceX_{0.0f};
    float forceY_{0.0f};
    float damp_{0.0f};
    float angle_{0.0f};
    float angularVelocity_{0.0f};
    float alpha_{255};

    float startY{0.0f};
    float bouncePower{-20.0f};
};

#endif