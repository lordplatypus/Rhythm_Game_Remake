#ifndef PARTICLE_MANAGER_H_
#define PARTICLE_MANAGER_H_
#include <vector>
#include "Particle.h"

class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();
    void Update(float delta_time);
    void Draw() const;
    
    void Explosion(float x, float y);
    void SquareExplosion(float x, float y);
    void WhiteOut(float x, float y);
    void FadeToBlack(float x, float y);
    void FadeFromBlack(float x, float y);
    void SmokeScreen(float x, float y);
    void Sparkle(float x, float y);

    void Clear();

private:
    std::vector<Particle*> particles;
};

#endif