#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Sprite sprite, float x, float y, float vx, float vy, float damp, float lifespan, float forceX, float forceY, float angle, float angularVelocity, 
        float startScale, float endScale, int red, int green, int blue, int startAlpha, int endAlpha, float progressSpeed = 1.0f);
    ~Particle();
    void Update(float delta_time);
    void Draw(sf::RenderWindow& render_window) const;
    bool IsDead() const;

private:  
    bool isDead = false; //Death flag(死亡フラグ)
    float x; //x coordinate(x座標)
    float y; //y coordinate(y座標)
    float lifespan = 0; //how long the particle will last(パーティクルの寿命)
    float age = 0; //current age of particle(パーティクルの歳)
    sf::Sprite sprite; //ID for particle sprite(パーティクルのID)
    float scale = 1.f; //particle scale(拡大率)
    float startScale = 1.f; //particle starting scale(開始の拡大率)
    float endScale = 1.f; //particle ending scale(終了の拡大率)
    float vx = 0; //x velocity(x速度)
    float vy = 0; //y velocity(y速度)
    float angularVelocity = 0; //angle velocity(向きの速度)
    float angularDamp = 1.f; //angle damp(角度の速度のブレーキ)
    float angle = 0; //angle(角度)
    float forceX = 0; //force the particle in the x direction(xにパーティクルを押す)
    float forceY = 0; //force the particle in the y direction(yにパーティクルを押す)
    float damp = 1.f; //dampen the particles velocity(速度のブレーキ)
    int red = 255; //red color(赤)
    int green = 255; //green color(緑)
    int blue = 255; //blue(青)
    int alpha = 255; //alpha(アルファ)
    int startAlpha = 255; //particles starting alpha(開始のアルファ)
    int endAlpha = 255; //particles ending alpha(終了のアルファ)
    float progressSpeed = 1.0f;
};

#endif