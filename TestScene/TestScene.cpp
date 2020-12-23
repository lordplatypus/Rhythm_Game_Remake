#include "TestScene.h"
#include "TestMap.h"
#include "../Assets/ID.h"
#include "../Engine/LP.h"
#include "../Engine/MP.h"
#include "../Engine/IP.h"
#include "../Engine/Math.h"
#include "../Player/Roboko.h"

TestScene::TestScene(Game* game) : game_{game}
{}

TestScene::~TestScene()
{}

void TestScene::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Test");
    if (saveState_) saveState_ = false;
    else
    {
        lem_ = new LocalEnemyManager(game_->GetGlobalEnemyManager());
        map_ = new TestMap(this, game_->GetCamera(), game_->GetPlayerManager(), lem_, game_->GetGlobalEnemyManager(), game_->GetTransitionManager(), &pm_);
        //MP::PlayMusic(Gain_Therapy);
        MP::PlayStageMusic(test_scene, true);
    }
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    transitionTo_ = "";

    //test
    game_->GetTransitionManager()->Lock("Title");
}

void TestScene::Update(float delta_time, float beat_time)
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

void TestScene::Draw(const sf::RenderWindow& render_window)
{
    map_->Draw(render_window);
    gameObjects_.Draw(render_window);
    gameObjects_.DelayedDraw(render_window);
    pm_.Draw(render_window); 
}

void TestScene::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* TestScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void TestScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void TestScene::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
    if (transitionTo_ == "JunkYard") saveState_ = true;
}

void TestScene::End()
{
    pm_.Clear();
    if (saveState_) return;
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
}