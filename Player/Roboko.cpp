#include <SFML/Graphics.hpp>
#include "Roboko.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"

Roboko::Roboko(sf::Vector2f position, Scene *scene, Camera* camera, PlayerManager* playerManager, TransitionManager* transitionManager, ParticleManager* particleManager, Map* map) : 
    camera_{camera}, playerManager_{playerManager}, transitionManager_{transitionManager}, pm_{particleManager}, map_{map}
{
    scene_ = scene;
    position_ = position;
    velocity_ = position;
    tag_ = "Player";
    name_ = "Roboko";
    imageWidth_ = 32;
    imageHeight_ = 32;
    //SetPerception(64);

    sprites_ = LP::SetMultiFrameSprite(roboko_texture, 32, 32, 8, 9);
    for (int i = 0; i < sprites_.size(); i++)
    {
        sprites_[i].setOrigin(sf::Vector2f(0.0f, imageHeight_ / 4));
    }

    deathText_ = LP::SetText("Press X to return to the Title", sf::Vector2f(0.0f, 0.0f), 32, sf::Vector2f(0.2f, 0.2f));
    deathText_.setOutlineThickness(5);
    deathText_.setOutlineColor(sf::Color::Black);
    deathText_.setFillColor(sf::Color(150, 150, 150));
    LP::SetTextOriginCenter(&deathText_);
    
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 10;

    playerManager_->GetHPUI()->SetBPM(MP::GetBPM(MP::GetPlayingMusic()));
}

Roboko::~Roboko()
{
    sprites_.clear();
}

void Roboko::Update(float delta_time, float beat_time)
{
    if (!IsDead())
    {
        InputHandle(delta_time, beat_time);
        AnimationHandle(delta_time, beat_time);
        velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);
        playerManager_->GetHPUI()->Update(delta_time, beat_time);
        playerManager_->GetWalletText()->setPosition(sf::Vector2f(camera_->GetCameraCenter().x + 8, camera_->GetCameraBottomEdge() - 16)); //offset text scale with x + 8
        sprites_[animCount_].setPosition(velocity_);
        SetSpriteHorizontalFlip(sprites_[animCount_], flip_);
    }
}

void Roboko::Draw(sf::RenderWindow& render_window) const
{
    if (!IsDead())
    {
        render_window.draw(sprites_[animCount_]);
    }
}

void Roboko::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (!IsDead())
    {
        playerManager_->GetHPUI()->Draw(render_window);
        render_window.draw(*playerManager_->GetWalletText());
    }
    else render_window.draw(deathText_);
}

void Roboko::InputHandle(float delta_time, float beat_time)
{
    attackType_ = -1;
    if (beat_time <= windowOfInput_)
    {   
        if (stunned) 
        {
            hasMoved_ = true;
            stunned = false;
        }
        if (!hasMoved_)
        {         
            if (state_ == CannonShoot)
            {
                state_ = CannonCoolDown;
                stunned = true;
                return;
            }  
            if (state_ != Normal && state_ != CannonRise && state_ != CannonPowerUp && state_ != CannonShoot) state_ = Normal;
            StorePosition();

            if (IP::PressLeft())
            {
                position_.x -= CellSize;
                hasMoved_ = true;
                flip_ = false;
                UseSkill();
            }
            else if (IP::PressRight())
            {
                position_.x += CellSize;
                hasMoved_ = true;
                flip_ = true;
                UseSkill();
            }
            else if (IP::PressUp())
            {
                position_.y -= CellSize;
                hasMoved_ = true;
                UseSkill();
            }
            else if (IP::PressDown())
            {
                position_.y += CellSize;
                hasMoved_ = true;
                UseSkill();
            }
            else if (IP::PressA())
            {
                attackType_ = 0;
                hasMoved_ = true;
                if (!flip_) 
                {
                    state_ = AttackLeft;
                    animCount_ = 16;
                }
                else 
                {
                    state_ = AttackRight;
                    animCount_ = 24;
                }
                UseSkill();
            }
            else if (IP::PressD())
            {
                attackType_ = 1;
                hasMoved_ = true;
                if (!flip_) 
                {
                    state_ = AttackRight;
                    animCount_ = 24;
                }
                else 
                {
                    state_ = AttackLeft;
                    animCount_ = 16;
                }
                UseSkill();
            }
            else if (IP::PressW())
            {
                attackType_ = 2;
                hasMoved_ = true;
                state_ = AttackUp;
                animCount_ = 7;
                UseSkill();
            }
            else if (IP::PressS())
            {
                attackType_ = 3;
                hasMoved_ = true;
                state_ = AttackDown;
                animCount_ = 32;
                UseSkill();
            }
            CheckMoveLocation();
        }
    }
    else 
    {
        hasMoved_ = false;
    }
}

void Roboko::AnimationHandle(float delta_time, float beat_time)
{
    timer_ += delta_time;
    if (state_ == Normal)
    {
        if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
        else if (animCount_ != 5 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (state_ == AttackUp) 
    {
        if (animCount_ != 15 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (state_ == Damage)
    {
        animCount_ = 6;
    }

    else if (state_ == CannonRise)
    {
        if (animCount_ != 43 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (state_ == CannonPowerUp)
    {
        if (animCount_ != 53 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (state_ == CannonShoot)
    {
        if (animCount_ != 58 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else if (state_ == CannonCoolDown)
    {
        if (animCount_ != 74 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }

    else 
    {
        if (state_ == AttackLeft)
        {
            if (animCount_ != 23 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
        else if (state_ == AttackRight) 
        {
            if (animCount_ != 31 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
        else if (state_ == AttackDown)        
        {
            if (animCount_ != 39 && timer_ >= timeInbetweenFrames_) 
            {
                animCount_++;
                timer_ = 0;
            }
        }
    }
}

void Roboko::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition")
    {
        if (transitionManager_->IsLocked(other.GetName())) return;
        stunned = true;
    }
    else if (other.GetTag() != "Bullet" && other.GetTag() != "Text")
    {
        position_ = GetPrevPosition();
        state_ = Damage;
    }
}

void Roboko::ReactInRange(GameObject& other)
{
    if (other.GetTag() == "Enemy")
    {
        other.SetInRangeOfPlayer(true);
        other.TakeDamage(attackType_);
    }
    else if (other.GetTag() == "Item")
    {
        other.TakeDamage(attackType_);
    }
}

void Roboko::ReactNotInRange(GameObject& other)
{
    if (other.GetTag() == "Enemy")
    {
        other.SetInRangeOfPlayer(false);
    }
}

void Roboko::SetPerception(const float perception)
{
    playerManager_->SetPerception(perception);
}

float Roboko::GetPerception() const
{
    return playerManager_->GetPerception();
}

void Roboko::TakeDamage(const int damage)
{
    if (IsDead()) return;
    pm_->WhiteOut(position_.x - 540, position_.y - 360);
    playerManager_->SubHP(damage);
    if (playerManager_->GetHP() <= 0) 
    {
        deathText_.setPosition(camera_->GetCameraCenter());
        Kill();
    }
}

void Roboko::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        position_ = GetPrevPosition();
        state_ = Damage;
    }
}

void Roboko::UseSkill()
{
    if (playerManager_->GetKillCount() <= cooldownBase) return;
    if (attackType_ == -1) 
    {
        prevAttackInput = -1;
        if (state_ != Normal)
        {
            state_ = Normal;
            animCount_ = 0;
        }
        return; //if no attack, return
    }
    if (skillCount >= 3)
    {
        skillCount = 0;
        prevAttackInput = -1;
    }

    if (prevAttackInput == attackType_) skillCount++;
    else skillCount = 0;
    prevAttackInput = attackType_;

    switch(skillCount)
    {
    case 1:
        animCount_ = 40;
        state_ = CannonRise;
        break;

    case 2:
        animCount_ = 44;
        state_ = CannonPowerUp;
        break;

    case 3:
        animCount_ = 54;
        state_ = CannonShoot;
        cooldownBase = playerManager_->GetKillCount() + playerManager_->GetSpecialCooldown();
        // if (flip_) scene_->AddGameObject(new CannonNormal(Vector2f{position_.x + imageWidth_, position_.y + imageHeight_ / 2}, Vector2f{500.0f, 0.0f}, scene_));
        // else scene_->AddGameObject(new CannonNormal(Vector2f{position_.x, position_.y + imageHeight_ / 2}, Vector2f{-500.0f, 0.0f}, scene_));
        break;
    }
}