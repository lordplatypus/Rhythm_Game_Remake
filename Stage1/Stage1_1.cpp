#include "Stage1_1.h"
#include "Map1_1.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"
#include "../Event/DefeatEnemies.h"
#include "../Event/Spawner.h"

Stage1_1::Stage1_1(Game* game) : game_{game}
{}

Stage1_1::~Stage1_1()
{}

void Stage1_1::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Stage1_1");
    if (saveState_) saveState_ = false;
    else
    {
        lem_ = new LocalEnemyManager(game_->GetGlobalEnemyManager());
        map_ = new Map1_1(this, game_->GetCamera(), game_->GetPlayerManager(), lem_, game_->GetTransitionManager(), &pm_);
        MP::PlayStageMusic(stage1_1, true);
        //AddGameObject(new DefeatEnemies("Stage1_2", game_->GetCamera(), game_->GetTransitionManager(), lem_));
        AddGameObject(new Spawner("Stage1_2", game_->GetCamera(), game_->GetTransitionManager(), this, lem_, game_->GetPlayerManager(), &pm_, map_));
    }
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    transitionTo_ = "";
}

void Stage1_1::Update(float delta_time, float beat_time)
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

void Stage1_1::Draw()
{
    map_->Draw();
    gameObjects_.Draw();
    gameObjects_.DelayedDraw();
    pm_.Draw();
}

void Stage1_1::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* Stage1_1::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void Stage1_1::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void Stage1_1::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
    if (transitionTo_ == "JunkYard") saveState_ = true;
}

void Stage1_1::End()
{
    pm_.Clear();
    if (saveState_) return;
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
}