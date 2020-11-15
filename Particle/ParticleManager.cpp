#include "ParticleManager.h"
#include "../Engine/LP.h"
#include "../Engine/Math.h"
#include "../Assets/ID.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
    Clear();
}

void ParticleManager::Update(float delta_time)
{
    for (auto i : particles)
    {
        if(!i->IsDead()) i->Update(delta_time);
    }

    for (auto i = particles.begin(); i != particles.end(); )
    {
        if ((*i)->IsDead())
        {
            delete *i;
            i = particles.erase(i);
        }
        else i++;
    }
}

void ParticleManager::Draw() const
{
    for (auto i : particles)
    {
        if (!i->IsDead()) i->Draw();
    }
}

void ParticleManager::Explosion(float x_, float y_)
{
    // for (int i = 0; i < 50; i++)
    // {
    //     int key = LP::SetSprite(smoke, sf::Vector2f(x_, y_));
    //     LP::SetSpriteOriginCenter(key);
    //     float lifespan = (rand() % 5 + 5) / 10.0f;
    //     float angle = (rand() % 360) * (M_PI / 180);
    //     float speed = rand() % 50 + 30;
    //     float vx = (float)cos(angle) * speed;
    //     float vy = (float)sin(angle) * speed;
    //     float endScale = (rand() % 2 + 1) / 10.0f;
    //     float startAlpha = rand() % 256;

    //     particles.push_back(new Particle(key, x_, y_, vx, vy, 1, lifespan, 0, -100.0f, 0, 0, .05f, endScale, 255, 255, 255, startAlpha, 0));
    // }

    // for (int i = 0; i < 100; i++)
    // {
    //     int key = LP::SetSprite(fire, sf::Vector2f(x_, y_));
    //     LP::SetSpriteOriginCenter(key);
    //     float lifespan = (rand() % 5 + 1) / 10.0f;
    //     float angle = (rand() % 360) * (M_PI / 180);
    //     float speed = rand() % 50 + 30;
    //     float vx = (float)cos(angle) * speed;
    //     float vy = (float)sin(angle) * speed;
    //     float endScale = (rand() % 2 + 1) / 10.0f;
    //     float startAlpha = rand() % 256;

    //     particles.push_back(new Particle(key, x_, y_, vx, vy, 1, lifespan, 0, 0, 0, 0, .05f, endScale, 255, 255, 255, startAlpha, 0));
    // }
}

void ParticleManager::SquareExplosion(float x_, float y_)
{
    // for (int i = 0; i < 50; i++)
    // {
    //     float speed = (rand() % 50) + 40;
    //     float vx = ((rand() % 20) - 10) * speed;
    //     float vy = ((rand() % 20) - 10) * speed;
    //     float startScale = (rand() % 10) / 10 + .5f;
    //     int startAlpha = rand() % 255;
    //     int red = rand() % 255;
    //     int green = rand() % 255;
    //     int blue = rand() % 255;

    //     particles.push_back(new Particle(LP::SetSprite(square8x8, sf::Vector2f(x_, y_)), x_, y_, vx, vy, .9f, 1, 0, 0, 0, 0, startScale, startScale+1, red, green, blue, startAlpha, 0));
    // }
}

void ParticleManager::WhiteOut(float x_, float y_)
{
    // particles.push_back(new Particle(LP::SetSprite(white, sf::Vector2f(x_, y_)), x_, y_, 0, 0, 1, .5f, 0, 0, 0, 0, 1, 1, 255, 255, 255, 255, 0));
}

void ParticleManager::FadeToBlack(float x_, float y_)
{
    // int key = LP::SetSprite(white, sf::Vector2f(x_, y_));
    // LP::SetSpriteOriginCenter(key);
    // particles.push_back(new Particle(key, x_, y_, 0, 0, 1, 1.0f, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 255));
}

void ParticleManager::FadeFromBlack(float x_, float y_)
{
    // int key = LP::SetSprite(white, sf::Vector2f(x_, y_));
    // LP::SetSpriteOriginCenter(key);
    // particles.push_back(new Particle(key, x_, y_, 0, 0, 1, 1.0f, 0, 0, 0, 0, 1, 1, 0, 0, 0, 255, 0));
}

void ParticleManager::SmokeScreen(float x_, float y_)
{
    // for (int i = 0; i < 100; i++)
    // {
    //     int key = LP::SetSprite(smoke, sf::Vector2f(x_, y_));
    //     LP::SetSpriteOriginCenter(key);
    //     float lifespan = (rand() % 10) / 10.0f;
    //     float vx = rand() % 200 - 100;
    //     float vy = -(rand() % 200);
    //     float angle = (rand() % 360) * (M_PI / 180);
    //     float startScale = (rand() % 2 + 2) / 10.0f;
    //     float endScale = (rand() % 2) / 10.0f;
    //     float startAlpha = rand() % 256;
    //     particles.push_back(new Particle(key, x_, y_, vx, vy, .98f, lifespan, 0, 150.f, angle, 0, startScale, endScale, 255, 255, 255, startAlpha, 0));
    // }
}

void ParticleManager::Sparkle(float x_, float y_)
{
    // int sparkleKey = LP::SetSprite(sparkle, sf::Vector2f(x_, y_));
    // LP::SetSpriteOriginCenter(sparkleKey);
    // float lifespan = (float)(rand() % 5 + 2) / 10.0f;
    // particles.push_back(new Particle(sparkleKey, x_, y_, 0, 0, 1, lifespan, 0, 0, 0, 0, .05f, .1f, 255, 255, 255, 255, 255));
}


void ParticleManager::Clear()
{
    for (auto particle : particles)
    {
        delete particle;
    }
    particles.clear();
}