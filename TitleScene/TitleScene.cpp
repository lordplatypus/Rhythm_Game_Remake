#include <iostream>
#include "TitleScene.h"
#include "TitleMap.h"
#include "../Assets/Assets.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"

TitleScene::TitleScene(Game* game) : game_{game}
{}

TitleScene::~TitleScene()
{}

void TitleScene::Init()
{
    //set up map
    map_ = new TitleMap(this);
    //set camera size
    game_->GetCamera()->SetCameraViewSize(360.0f, 240.0f);
    //play music
    MP::PlayStageMusic(title_scene, true);
    //set up ranom
    srand(time(NULL));
    //get the last selected char    
    // playerSprite_ = LP::SetSprite(roboko_texture, 32, 32, 6, 1);
    // playerSprite2_ = LP::SetSprite(roboko_texture, 32, 32, 6, 1);
    playerSprite_ = LP::SetMultiFrameSprite(roboko_texture, 32, 32, 6, 1);
    playerSprite2_ = LP::SetMultiFrameSprite(roboko_texture, 32, 32, 6, 1);
    framesInOneAnimCycle = 5;
    endingFrame_ = 5;

    //set sprite origin and scale
    for (auto i : playerSprite_)
    {
        //LP::SetSpriteScale(i, .5f, .5f);
        // LP::SetSpriteOrigin(i, sf::Vector2f(0.0f, 8));
        // LP::SetSpriteHorizontalFlip(i, true);
        i.setOrigin(sf::Vector2f(0.0f, 8));
        LP::SetSpriteHorizontalFlip(i, true);
    }
    for (auto i : playerSprite2_)
    {
        //LP::SetSpriteScale(i, 2.0f, 2.0f);
        i.setScale(2.0f, 2.0f);
    }
    //set char position
    position_ = sf::Vector2f(13 * CellSize, 4 * CellSize);
    //create text
    // infoText = LP::SetText("Title Scene\nPress Z to Start", sf::Vector2f(32, 64), 32);
    // LP::SetTextScale(infoText, .1f, .1f);
    infoText_ = LP::SetText("Title Scene\nPress Z to Start", sf::Vector2f(32, 64), 32, sf::Vector2f(0.1f, 0.1f));
    //create background picture
    background_ = LP::SetSprite(title_scene_texture);
    //background = LP::SetSprite(title_scene_texture, sf::Vector2f(0, 0));
    //set up timing for animations
    timeInbetweenFrames_ = MP::GetBPM(MP::GetPlayingMusic()) / 10;
    windowOfInput_ = MP::GetBPM(MP::GetPlayingMusic()) / 2;

    pm_.FadeFromBlack(position_.x, position_.y);

    //Reset
    game_->GetPlayerManager()->Init();
    game_->GetGlobalEnemyManager()->Clear();
}

void TitleScene::Update(float delta_time, float beat_time)
{
    if (beat_time <= windowOfInput_)
    {
        if (oncePerBeat) 
        {
            MovementHandle();
            oncePerBeat = false;
        }
    }
    else oncePerBeat = true;
    
    AnimationHandle(delta_time, beat_time);

    velocity_ = Math::Lerp(velocity_, position_, 10 * delta_time);
    game_->GetCamera()->SetTarget(velocity_ + sf::Vector2f(8, 8));

    //LP::SetTextPosition(infoText, sf::Vector2f(game_->GetCamera()->GetCameraLeftEdge() + 10, game_->GetCamera()->GetCameraTopEdge() + 10));
    playerSprite_[animCount_].setPosition(velocity_);
    playerSprite2_[animCount_].setPosition(sf::Vector2f(game_->GetCamera()->GetCameraRightEdge() - 64, game_->GetCamera()->GetCameraBottomEdge() - 64));
    background_.setPosition(sf::Vector2f(game_->GetCamera()->GetCameraLeftEdge(), game_->GetCamera()->GetCameraTopEdge()));
    infoText_.setPosition(sf::Vector2f(game_->GetCamera()->GetCameraLeftEdge() + 10, game_->GetCamera()->GetCameraTopEdge() + 10));

    pm_.Update(delta_time);

    if (IP::PressZ())
    {
        game_->ChangeScene("Lobby");
    }
    if (IP::PressX())
    {
        game_->ChangeScene("BPM");
    }
}

void TitleScene::MovementHandle()
{
    position_.x += CellSize; //move right
    if (position_.x == 43 * CellSize)
    {//reset position to make it look like an infinte loop
        position_.x = 13 * CellSize;
        velocity_.x = 12 * CellSize; //this is needed to keep the illusion that this is a loop (camera would all of the sudden scroll left otherwise)
    }
}

void TitleScene::AnimationHandle(float delta_time, float beat_time)
{
    timer_ += delta_time;
    if (beat_time <= timeInbetweenFrames_) animCount_ = 0;     
    else if (animCount_ != endingFrame_ && timer_ >= timeInbetweenFrames_) 
    {
        animCount_++;
        timer_ = 0;
    }
}

void TitleScene::Draw(sf::RenderWindow& render_window)
{
    map_->Draw(render_window);

    // LP::DrawSprite(playerSprite_[animCount_], velocity_); //The smaller moving char
    // LP::DrawSprite(playerSprite2_[animCount_], sf::Vector2f(game_->GetCamera()->GetCameraRightEdge() - 64, game_->GetCamera()->GetCameraBottomEdge() - 64));
    // LP::DrawSprite(background, sf::Vector2f(game_->GetCamera()->GetCameraLeftEdge(), game_->GetCamera()->GetCameraTopEdge()));
    // LP::DrawText(infoText);
    render_window.draw(playerSprite_[animCount_]);
    render_window.draw(playerSprite2_[animCount_]);
    render_window.draw(background_);
    render_window.draw(infoText_);

    pm_.Draw(render_window);
}

void TitleScene::AddGameObject(GameObject* gameObject)
{}

GameObject* TitleScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    return nullptr;
}

void TitleScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void TitleScene::ChangeScene(const std::string& sceneName)
{
    game_->ChangeScene(sceneName);
}

void TitleScene::End()
{
    playerSprite_.clear();
    playerSprite2_.clear();
    pm_.Clear();
    delete map_;
}