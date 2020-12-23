#ifndef MORTAR_H_
#define MORTAR_H_
#include "../Gameobjects/GameObject.h"
#include "LocalEnemyManager.h"
#include "../Particle/ParticleManager.h"
#include "EnemyData.h"

class Mortar : public GameObject
{
public:
    Mortar(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, ParticleManager* pm);
    ~Mortar();
    void Update(float delta_time, float beat_time) override;
    void Draw(const sf::RenderWindow& render_window) override;
    void Kill() override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    LocalEnemyManager* lem_{nullptr};
    ParticleManager* pm_{nullptr};
    EnemyData* ed_{nullptr};

    int deathCount_{3};
    float windowOfInput_{0.0f};
    bool input_{false};
    float scale_{0.3f};
    float endingScale_{1.3f};
};

#endif