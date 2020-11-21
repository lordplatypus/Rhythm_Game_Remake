#include "Stage1_2.h"
#include "Map1_2.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"

Stage1_2::Stage1_2(Game* game) : game_{game}
{}

Stage1_2::~Stage1_2()
{}

void Stage1_2::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Stage1_2");
    if (saveState_) saveState_ = false;
    else
    {
        lem_ = new LocalEnemyManager(game_->GetGlobalEnemyManager());
        map_ = new Map1_2(this, game_->GetCamera(), game_->GetPlayerManager(), lem_, game_->GetTransitionManager(), &pm_);
        //MP::PlayMusic(Gain_Therapy);
        MP::PlayStageMusic(stage1_2, true);
    }
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    transitionTo_ = "";
}

void Stage1_2::Update(float delta_time, float beat_time)
{
    gameObjects_.Update(delta_time, beat_time);
    gameObjects_.Collision();
    gameObjects_.Perception();
    gameObjects_.Remove();
    pm_.Update(delta_time);

    if (gameObjects_.Find("Player") != nullptr) 
        game_->GetCamera()->SetTarget(Math::Lerp(game_->GetCamera()->GetCameraCenter(), gameObjects_.Find("Player")->GetPosition() + sf::Vector2f(8, 8), 10 * delta_time));

    if (transitionTo_ != "") game_->ChangeScene(transitionTo_);

    if (IP::PressX())
    {//Return to TitleScene
        game_->ChangeScene("Title");
    }
}

void Stage1_2::Draw()
{
    map_->Draw();
    gameObjects_.Draw();
    gameObjects_.DelayedDraw();
    pm_.Draw();
}

void Stage1_2::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* Stage1_2::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void Stage1_2::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void Stage1_2::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
    if (transitionTo_ == "JunkYard") saveState_ = true;
}

void Stage1_2::End()
{
    pm_.Clear();
    if (saveState_) return;
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
}