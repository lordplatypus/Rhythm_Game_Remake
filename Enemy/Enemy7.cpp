#include <SFML/Graphics.hpp>
#include "Enemy7.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"
#include "../Assets/ID.h"
#include "Mortar.h"
#include "BulletCasing.h"

Enemy7::Enemy7(sf::Vector2f position, Scene *scene, LocalEnemyManager* lem, PlayerManager* playerManager, ParticleManager* pm, Map* map)
{
    scene_ = scene;
    lem_ = lem;
    playerManager_ = playerManager;
    pm_ = pm;
    position_ = position;
    map_ = map;
    HP_ = 4 + lem_->GetMaxHPModifier();
    tag_ = "Enemy";
    name_ = "7";
    imageWidth_ = 32;
    imageHeight_ = 32;

    ed_ = lem_->Add(HP_, HP_, 1, CellSize*7, true, 1, false);

    enemySprite_ = LP::SetMultiFrameSprite(artillery_texture, 32, 32, 4, 5);
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 10.0f;
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    arrow_ = new UIArrow(pm_, position_, HP_);
}

Enemy7::~Enemy7()
{
}

void Enemy7::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (!hasMoved_) 
        {
            StorePosition();
            if (state_ == Active)
            {
                beatCount_++;
                if (beatCount_ == 3 && !scene_->FindGameObject("Player")->IsDead())
                {
                    beatCount_ = 0;
                    state_ = Angery;
                }
            }
            else if (state_ == Angery) 
            {
                state_ = Fire;
                sf::Vector2f casePosition;
                if (flip_) casePosition = sf::Vector2f(position_.x + 9, position_.y + 18);
                else casePosition = sf::Vector2f(position_.x + 23, position_.y + 18);
                scene_->AddGameObject(new BulletCasing(casePosition, flip_, scene_, pm_, map_));
                pm_->Explosion(position_.x + 16, position_.y + 4);
            }
            else if (state_ == Fire)
            {
                FireMortar();
                //Add smoke particle effect here
                state_ = Active;
            }
            else if (state_ == Retreat)
            {
                beatCount_++;
                if (beatCount_ == 3 && !scene_->FindGameObject("Player")->IsDead())
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
                    //Reverse Direction
                    if (position_.x / CellSize > moveTo.x) moveTo.x += 2;
                    else if (position_.x / CellSize  < moveTo.x) moveTo.x -= 2;
                    if (position_.y / CellSize  > moveTo.y) moveTo.y += 2;
                    else if (position_.y / CellSize  < moveTo.y) moveTo.y -= 2;
                    //convert back into world coordinates
                    moveTo.x *= CellSize;
                    moveTo.y *= CellSize;
                    //move to location
                    position_ = moveTo;
                    //check to see if they went into wall
                    CheckMoveLocation();
                }
            }
        }       
        hasMoved_ = true;
    }
    else hasMoved_ = false;

    AnimationHandle(delta_time, beat_time);

    velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);
    enemySprite_[animCount_].setPosition(velocity_);
    SetSpriteHorizontalFlip(enemySprite_[animCount_], flip_);

    arrow_->Update(delta_time, beat_time);
    arrow_->UpdatePosition(velocity_);
}

void Enemy7::Draw(sf::RenderWindow& render_window) const
{
    if (lem_->GetVisibilityModifier() || GetInRangeOfPlayer()) render_window.draw(enemySprite_[animCount_]);
}

void Enemy7::DelayedDraw(sf::RenderWindow& render_window) const
{
    if (GetInRangeOfPlayer()) arrow_->Draw(render_window);
}

void Enemy7::FireMortar()
{
    sf::Vector2f playerPosition = scene_->FindGameObject("Player")->GetPosition();
    int direction = rand() % 5;
    switch (direction)
    {
        case 0:
        playerPosition.x -= CellSize;
        break;

        case 1:
        playerPosition.x += CellSize;
        break;

        case 2:
        playerPosition.y -= CellSize;
        break;

        case 3:
        playerPosition.y += CellSize;
        break;

        default:
        break;
    }

    if (map_->IsWall(playerPosition)) playerPosition = scene_->FindGameObject("Player")->GetPosition();
    playerPosition.x += 16.0f;
    playerPosition.y += 16.0f;
    scene_->AddGameObject(new Mortar(playerPosition, scene_, lem_, pm_));
}

void Enemy7::ReactOnCollision(GameObject& other)
{
    if (other.GetTag() == "Transition") return;
    if (other.GetTag() == "Player")
    {
        other.TakeDamage(ed_->atk_ + lem_->GetAtkModifier());
    }
    position_ = GetPrevPosition();
}

void Enemy7::ReactInRange(GameObject& other)
{
    if (other.GetTag() == "Player") 
    {
        if (sf::IntRect(position_.x - CellSize*2, position_.y - CellSize*2, imageWidth_ + CellSize*2*2, imageHeight_ + CellSize*2*2).intersects(other.GetHitBox())) state_ = Retreat;
        else if (state_ != Angery && state_ != Fire) state_ = Active;
    }
}

void Enemy7::ReactNotInRange(GameObject& other)
{
    if (other.GetTag() == "Player") 
    {
        state_ = Rest;
    }
}

void Enemy7::AnimationHandle(float delta_time, float beat_time)
{   
    timer_ += delta_time;

    if (beat_time <= timeInbetweenFrames_) 
    {
        if (state_ == Rest || state_ == Active || state_ == Retreat) 
        {
            animCount_ = 0;
            endFrame_ = 3;
        }
        else if (state_ == Angery)
        {
            animCount_ = 4;
            endFrame_ = 7;
        }
        else if (state_ == Fire)
        {
            animCount_ = 8;
            endFrame_ = 16;
        }
    }
    else if (animCount_ != endFrame_ && timer_ >= timeInbetweenFrames_) 
    {
        animCount_++;
        timer_ = 0;
    }

    if (animCount_ == 11) 
    {
        
    } //bullet casing particle goes here
}

void Enemy7::CheckMoveLocation()
{
    if (map_->IsWall(position_))
    {
        position_ = GetPrevPosition();
    }
}

void Enemy7::DFSPriorityDirection(sf::Vector2f current, sf::Vector2f end)
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

sf::Vector2f Enemy7::DFS(sf::Vector2f location, std::vector<sf::Vector2f> visited, sf::Vector2f end, int depth)
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

void Enemy7::DFSFinish(sf::Vector2f current, sf::Vector2f end)
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
        flip_ = true; //reversed because it runs away
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
        flip_ = false; //reversed because it runs away
    }
}