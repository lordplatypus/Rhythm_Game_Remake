#include "StartingItemScene.h"
#include "StartingItemMap.h"
#include "../Assets/ID.h"
#include "../Engine/IP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"

StartingItemScene::StartingItemScene(Game* game) : game_{game}
{}

StartingItemScene::~StartingItemScene()
{}

void StartingItemScene::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Item");
    map_ = new StartingItemMap(this, game_->GetCamera(), game_->GetPlayerManager(), game_->GetGlobalEnemyManager(), game_->GetTransitionManager(), &pm_);
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    MP::PlayStageMusic(lobby_scene, true);
    transitionTo_ = "";
}

void StartingItemScene::Update(float delta_time, float beat_time)
{
    gameObjects_.Update(delta_time, beat_time);
    gameObjects_.Collision();
    gameObjects_.Perception();
    gameObjects_.Remove();
    pm_.Update(delta_time);

    game_->GetCamera()->SetTarget(Math::Lerp(game_->GetCamera()->GetCameraCenter(), gameObjects_.Find("Player")->GetPosition() + sf::Vector2f(8, 8), 10 * delta_time));

    if (transitionTo_ != "") game_->ChangeScene(transitionTo_);

    if (IP::PressX())
    {//Return to TitleScene
        game_->ChangeScene("Lobby");
    }
}

void StartingItemScene::Draw(sf::RenderWindow& render_window)
{
    map_->Draw(render_window);
    gameObjects_.Draw(render_window);
    gameObjects_.DelayedDraw(render_window);
    pm_.Draw(render_window);
}

void StartingItemScene::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* StartingItemScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void StartingItemScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void StartingItemScene::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
}

void StartingItemScene::End()
{
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
    pm_.Clear();
}