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

    sprite_ = LP::SetRectangle(position_, imageWidth_, imageHeight_);

    // enemySprite_ = LP::SetSprite(companion_texture, 32, 32, 8, 1);
    // for (auto i : enemySprite_)
    // {
    //     LP::SetSpriteOrigin(i, Vector2f(6,6));
    // }
    // timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 8.0f;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Generator::~Generator()
{
    // for (auto i : enemySprite_)
    // {
    //     LP::DeleteSprite(i);
    // }
    LP::DeleteRectangle(sprite_);
}

void Generator::Update(float delta_time, float beat_time)
{
    AnimationHandle(delta_time, beat_time);
    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(position_);
}

void Generator::Draw()
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) LP::DrawRectangle(sprite_, position_);
}

void Generator::DelayedDraw()
{
    if (GetInRangeOfPlayer()) arrow_->Draw();
}

void Generator::Kill()
{
    isDead_ = true;
    //event_->EventTrigger();
}

void Generator::ReactOnCollision(GameObject& other)
{
    
}