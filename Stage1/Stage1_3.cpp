#include "Stage1_3.h"
#include "Map1_3.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"
//Events
#include "../Event/DefeatEnemies.h"
#include "../Event/Spawner.h"
#include "../Event/FindKeys.h"
#include "../Event/InvisibleEnemies.h"
#include "../Event/MortarStrike.h"

Stage1_3::Stage1_3(Game* game) : game_{game}
{}

Stage1_3::~Stage1_3()
{}

void Stage1_3::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Stage1_3");
    if (saveState_) saveState_ = false;
    else
    {
        lem_ = new LocalEnemyManager(game_->GetGlobalEnemyManager());
        map_ = new Map1_3(this, game_->GetCamera(), game_->GetPlayerManager(), lem_, game_->GetGlobalEnemyManager(), game_->GetTransitionManager(), &pm_);
        MP::PlayStageMusic(stage1_3, true);
        RandomEvent();
    }
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    transitionTo_ = "";
}

void Stage1_3::Update(float delta_time, float beat_time)
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

void Stage1_3::Draw()
{
    map_->Draw();
    gameObjects_.Draw();
    gameObjects_.DelayedDraw();
    pm_.Draw();
}

void Stage1_3::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* Stage1_3::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void Stage1_3::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void Stage1_3::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
    if (transitionTo_ == "JunkYard") saveState_ = true;
}

void Stage1_3::End()
{
    pm_.Clear();
    if (saveState_) return;
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
}

void Stage1_3::RandomEvent()
{
    int randEvent = rand() % 6;
    const std::string& transitionTo = "Title";
    switch (randEvent)
    {
        case 0:
        AddGameObject(new DefeatEnemies(transitionTo, game_->GetCamera(), game_->GetTransitionManager(), lem_));
        break;

        case 1:
        AddGameObject(new Spawner(transitionTo, game_->GetCamera(), game_->GetTransitionManager(), this, lem_, game_->GetPlayerManager(), &pm_, map_));
        break;

        case 2:
        AddGameObject(new FindKeys(transitionTo, game_->GetCamera(), game_->GetTransitionManager(), game_->GetPlayerManager(), this, &pm_, map_));
        break;

        case 3:
        AddGameObject(new InvisibleEnemies(transitionTo, game_->GetCamera(), game_->GetTransitionManager(), game_->GetPlayerManager(), this, &pm_, map_, lem_));
        break;

        case 4:
        AddGameObject(new MortarStrike(transitionTo, game_->GetCamera(), game_->GetTransitionManager(), game_->GetPlayerManager(), this, lem_, &pm_, map_));
        break;

        default:
        break;
    }
}