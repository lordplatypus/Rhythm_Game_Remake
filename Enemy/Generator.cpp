#include <SFML/Graphics.hpp>
#include "Generator.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Assets/ID.h"
using namespace std;
using namespace sf;

Generator::Generator(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    //event_ = event;
    HP_ = 3 + lem_->GetMaxHPModifier();
    tag_ = "Enemy";
    name_ = "Generator";
    imageWidth_ = 32;
    imageHeight_ = 32;

    ed_ = lem_->Add(HP_, HP_, 1, 0, true, 1, false);

    // sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);

    // enemySprite_ = LP::SetSprite(companion_texture, 32, 32, 8, 1);
    // for (auto i : enemySprite_)
    // {
    //     LP::SetSpriteOrigin(i, Vector2f(6,6));
    // }

    enemySprite_ = LP::SetMultiFrameSprite(generator_texture, 32, 32, 6, 1);
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 8.0f;

    enemyrect_.setSize(sf::Vector2f(26, 25));
    enemyrect_.setPosition(position_ + sf::Vector2f(3.0f, 3.0f));
    enemyrect_.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Generator::~Generator()
{
    // for (auto i : enemySprite_)
    // {
    //     LP::DeleteSprite(i);
    // }
   // LP::DeleteRectangle(sprite_);
}

void Generator::Update(float delta_time, float beat_time)
{
    AnimationHandle(delta_time, beat_time);
    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(position_);
    enemySprite_[animCount_].setPosition(position_);
}

void Generator::Draw(sf::RenderWindow& render_window) const
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) 
    {
        render_window.draw(enemyrect_);
        render_window.draw(enemySprite_[animCount_]);
    }
}

void Generator::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (GetInRangeOfPlayer()) arrow_->Draw(render_window);
}

void Generator::Kill()
{
    isDead_ = true;
    //event_->EventTrigger();
}

void Generator::ReactOnCollision(GameObject& other)
{
    
}

void Generator::AnimationHandle(float delta_time, float beat_time)
{   
    timer_ += delta_time;
    if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
    else if (animCount_ != 5 && timer_ >= timeInbetweenFrames_) 
    {
        animCount_++;
        timer_ = 0;
    }
}