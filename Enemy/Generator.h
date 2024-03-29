#ifndef GENERATOR_H_
#define GENERATOR_H_
#include <vector>
#include "Enemy.h"
//#include "../Event/Event.h"

class Generator : public Enemy
{
public:
    Generator(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map);
    ~Generator() override;
    void Update(float delta_time, float beat_time) override;
    void Draw(sf::RenderWindow& render_window) const override;
    void DelayedDraw(sf::RenderWindow& render_window) const override;
    void Kill() override;

private:
    void ReactOnCollision(GameObject& other) override;
    void AnimationHandle(float delta_time, float beat_time) override;

private:
    //Event* event_{nullptr};
    sf::RectangleShape enemyrect_;
};

#endif