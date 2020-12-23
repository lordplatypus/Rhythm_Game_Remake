#include <SFML/Graphics.hpp>
#include "Enemy3.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Assets/ID.h"
#include "../Engine/Math.h"

Enemy3::Enemy3(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    HP_ = 8 + lem_->GetMaxHPModifier();
    position_ = position;
    tag_ = "Enemy";
    name_ = "3";
    imageWidth_ = 32;
    imageHeight_ = 32;
    // SetLeft(0);
    // SetRight(imageWidth_);
    // SetTop(0);
    // SetBottom(imageHeight_);
    numOfBeatsBetweenAttacks_ = 4;
    flip_ = false;

    ed_ = lem_->Add(HP_, HP_, 1, 64, true, 1, false);

    enemySprite_ = LP::SetSprite(surveillance_texture, 32, 32, 4, 2);
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 4 / 2;
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Enemy3::~Enemy3()
{
    for (auto i : enemySprite_)
    {
        LP::DeleteSprite(i);
    }
}

void Enemy3::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (!hasMoved_) 
        {
            StorePosition();
            if (state_ == Rest) {}
            else if (state_ == Normal)
            {
                beatCount_++;
                if (beatCount_ == 4 && !scene_->FindGameObject("Player")->IsDead())
                {
                    beatCount_ = 0;
                    //start of DFS
                    //Player location - converted to a format that the map understands (worldLoc / CellSize)
                    sf::Vector2f playerLoc((int)(scene_->FindGameObject("Player")->GetPosition().x / CellSize), (int)(scene_->FindGameObject("Player")->GetPosition().y / CellSize));
                    //Enemy location
                    sf::Vector2f enemyLoc((int)(position_.x / CellSize), (int)(position_.y / CellSize));
                    //vector that will store "visited" locations
                    std::vector<sf::Vector2f> visited;
                    //Start DFS
                    sf::Vector2f moveTo = DFS(playerLoc, visited, enemyLoc, 0);
                    //reset bool that tells DFS to stop its search
                    finish_ = false;
                    //convert back into world coordinates
                    moveTo.x *= CellSize;
                    moveTo.y *= CellSize;
                    //move to location
                    position_ = moveTo;
                    //check to see if they went into wall (shouldn't happen by normal movement)
                    CheckMoveLocation();
                }
            }
        }       
        hasMoved_ = true;
    }
    else if (delayAttack_)
    {
        StorePosition();
        position_.x = delayMoveX_;
        position_.y = delayMoveY_;        
        delayAttack_ = false;
    }
    else hasMoved_ = false;

    AnimationHandle(delta_time, beat_time);

    velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(velocity_);
}

void Enemy3::Draw(const sf::RenderWindow& render_window)
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer())
    {
        LP::SetSpriteHorizontalFlip(enemySprite_[animCount_], flip_);
        LP::DrawSprite(enemySprite_[animCount_], velocity_);
    }
}

void Enemy3::DelayedDraw(const sf::RenderWindow& render_window)
{
    if (GetInRangeOfPlayer()) arrow_->Draw(render_window);
}

void Enemy3::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition") return;
    if (other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
    position_ = GetPrevPosition();
    beatCount_ = 3;
}

void Enemy3::ReactInRange(GameObject& other)
{
    if (other.GetTag() == "Player") 
    {
        state_ = Normal;
    }
}

void Enemy3::ReactNotInRange(GameObject& other)
{}

void Enemy3::AnimationHandle(float delta_time, float beat_time)
{   
    timer_ += delta_time;
    if (beatCount_ == 3)
    {
        if (beat_time <= timeInbetweenFrames_) animCount_ = 4;     
        else if (animCount_ != 7 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
    else
    {
        if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
        else if (animCount_ != 3 && timer_ >= timeInbetweenFrames_) 
        {
            animCount_++;
            timer_ = 0;
        }
    }
}

void Enemy3::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        position_ = GetPrevPosition();
    }

    if (position_ == scene_->FindGameObject("Player")->GetPosition())
    {
        delayMoveX_ = position_.x;
        delayMoveY_ = position_.y;
        position_ = GetPrevPosition();
        delayAttack_ = true;
    }
}

void Enemy3::DFSPriorityDirection(sf::Vector2f current, sf::Vector2f end)
{
    if (current.x == end.x)
    {
        if (current.y > end.y)
        {
            move1_ = sf::Vector2f(current.x, current.y - 1);
            move2_ = sf::Vector2f(current.x - 1, current.y);
            move3_ = sf::Vector2f(current.x + 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y + 1);
            return;
        }
        else if (current.y < end.y)
        {
            move1_ = sf::Vector2f(current.x, current.y + 1);
            move2_ = sf::Vector2f(current.x - 1, current.y);
            move3_ = sf::Vector2f(current.x + 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y - 1);
            return;
        }
    }
    else if (current.y == end.y)
    {
        if (current.x > end.x)
        {
            move1_ = sf::Vector2f(current.x - 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y - 1);
            move3_ = sf::Vector2f(current.x, current.y + 1);
            move4_ = sf::Vector2f(current.x + 1, current.y);
            return;
        }
        else if (current.x < end.x)
        {
            move1_ = sf::Vector2f(current.x + 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y - 1);
            move3_ = sf::Vector2f(current.x, current.y + 1);
            move4_ = sf::Vector2f(current.x - 1, current.y);
            return;
        }
    }
    else if (current.x < end.x && current.y > end.y)
    {
        if (end.x - current.x >= current.y - end.y)
        {
            move1_ = sf::Vector2f(current.x + 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y - 1);
            move3_ = sf::Vector2f(current.x, current.y + 1);
            move4_ = sf::Vector2f(current.x - 1, current.y);
            return;
        }
        else
        {
            move1_ = sf::Vector2f(current.x, current.y - 1);
            move2_ = sf::Vector2f(current.x + 1, current.y);
            move3_ = sf::Vector2f(current.x - 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y + 1);
            return;
        }
    }
    else if (current.x > end.x && current.y > end.y)
    {
        if (current.x - end.x >= current.y - end.y)
        {
            move1_ = sf::Vector2f(current.x - 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y - 1);
            move3_ = sf::Vector2f(current.x, current.y + 1);
            move4_ = sf::Vector2f(current.x + 1, current.y);
            return;
        }
        else
        {
            move1_ = sf::Vector2f(current.x, current.y - 1);
            move2_ = sf::Vector2f(current.x - 1, current.y);
            move3_ = sf::Vector2f(current.x + 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y + 1);
            return;
        }
    }
    else if (current.x > end.x && current.y < end.y)
    {
        if (current.x - end.x >= end.y - current.y)
        {
            move1_ = sf::Vector2f(current.x - 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y + 1);
            move3_ = sf::Vector2f(current.x, current.y - 1);
            move4_ = sf::Vector2f(current.x + 1, current.y);
            return;
        }
        else
        {
            move1_ = sf::Vector2f(current.x, current.y + 1);
            move2_ = sf::Vector2f(current.x - 1, current.y);
            move3_ = sf::Vector2f(current.x + 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y - 1);
            return;
        }
    }
    else if (current.x < end.x && current.y < end.y)
    {
        if (end.x - current.x >= end.y - current.y)
        {
            move1_ = sf::Vector2f(current.x + 1, current.y);
            move2_ = sf::Vector2f(current.x, current.y + 1);
            move3_ = sf::Vector2f(current.x, current.y - 1);
            move4_ = sf::Vector2f(current.x - 1, current.y);
            return;
        }
        else
        {
            move1_ = sf::Vector2f(current.x, current.y + 1);
            move2_ = sf::Vector2f(current.x + 1, current.y);
            move3_ = sf::Vector2f(current.x - 1, current.y);
            move4_ = sf::Vector2f(current.x, current.y - 1);
            return;
        }
    }
}

sf::Vector2f Enemy3::DFS(sf::Vector2f location, std::vector<sf::Vector2f> visited, sf::Vector2f end, int depth)
{
    depth++;
    if (depth >= 20) return end;

    sf::Vector2f moveTo = end;

    sf::Vector2f currentLoc = location;
    visited.push_back(currentLoc);

    DFSFinish(currentLoc, end);
    if (finish_) return currentLoc;

    DFSPriorityDirection(currentLoc, end);
    bool canMove1 = true;
    bool canMove2 = true;
    bool canMove3 = true;
    bool canMove4 = true;

    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i] == move1_) canMove1 = false;
        if (visited[i] == move2_) canMove2 = false;
        if (visited[i] == move3_) canMove3 = false;
        if (visited[i] == move4_) canMove4 = false;
    }

    if (map_->IsWall(sf::Vector2f(move1_.x * CellSize, move1_.y * CellSize)))canMove1 = false;
    if (map_->IsWall(sf::Vector2f(move2_.x * CellSize, move2_.y * CellSize)))canMove2 = false;
    if (map_->IsWall(sf::Vector2f(move3_.x * CellSize, move3_.y * CellSize)))canMove3 = false;
    if (map_->IsWall(sf::Vector2f(move4_.x * CellSize, move4_.y * CellSize)))canMove4 = false;

    if (canMove1 && !finish_)
    {
        moveTo = DFS(move1_, visited, end, depth);
    }
    if (canMove2 && !finish_)
    {
        moveTo = DFS(move2_, visited, end, depth);
    }
    if (canMove3 && !finish_)
    {
        moveTo = DFS(move3_, visited, end, depth);
    }
    if (canMove4 && !finish_)
    {
        moveTo = DFS(move4_, visited, end, depth);
    }

    return moveTo;
}

void Enemy3::DFSFinish(sf::Vector2f current, sf::Vector2f end)
{
    if (finish_) return;

    if (current.x == end.x &&
        current.y - 1 == end.y)
    { //up
        finish_ = true;
    }
    else if (current.x + 1 == end.x &&
             current.y == end.y)
    { //right
        finish_ = true;
        flip_ = false;
    }
    else if (current.x == end.x &&
             current.y + 1 == end.y)
    { //down
        finish_ = true;
    }
    else if (current.x - 1 == end.x &&
             current.y == end.y)
    { //left
        finish_ = true;
        flip_ = true;
    }
}