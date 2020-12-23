#include "LobbyScene.h"
#include "LobbyMap.h"
#include "../Assets/ID.h"
#include "../Engine/IP.h"
#include "../Engine/MP.h"
#include "../Engine/Math.h"

LobbyScene::LobbyScene(Game* game) : game_{game}
{}

LobbyScene::~LobbyScene()
{}

void LobbyScene::Init()
{
    game_->GetTransitionManager()->SetCurrentScene("Lobby");
    // game_->GetPlayerManager()->Init();
    // game_->GetGlobalEnemyManager()->Clear();
    map_ = new LobbyMap(this, game_->GetCamera(), game_->GetPlayerManager(), game_->GetTransitionManager(), &pm_);
    game_->GetCamera()->SetCameraViewSize(360.f, 240.f);
    game_->GetCamera()->SetTarget(gameObjects_.Find("Player")->GetPosition());
    pm_.FadeFromBlack(gameObjects_.Find("Player")->GetPosition().x, gameObjects_.Find("Player")->GetPosition().y);
    MP::PlayStageMusic(lobby_scene, true);
    transitionTo_ = "";
}

void LobbyScene::Update(float delta_time, float beat_time)
{
    gameObjects_.Update(delta_time, beat_time);
    gameObjects_.Collision();
    gameObjects_.Perception();
    gameObjects_.Remove();
    pm_.Update(delta_time);


    //game_->GetCamera()->SetTarget(gameObjects.Find("Player")->GetPosition() + Vector2f(8, 8));
    game_->GetCamera()->SetTarget(Math::Lerp(game_->GetCamera()->GetCameraCenter(), gameObjects_.Find("Player")->GetPosition() + sf::Vector2f(8, 8), 10 * delta_time));

    if (transitionTo_ != "") game_->ChangeScene(transitionTo_);

    if (IP::PressX())
    {//Return to TitleScene
        game_->ChangeScene("Title");
    }
}

void LobbyScene::Draw(sf::RenderWindow& render_window)
{
    map_->Draw(render_window);
    gameObjects_.Draw(render_window);
    gameObjects_.DelayedDraw(render_window);
    pm_.Draw(render_window);
}

void LobbyScene::AddGameObject(GameObject* gameObject)
{
    gameObjects_.Add(gameObject);
}

GameObject* LobbyScene::FindGameObject(const std::string& string, const bool byTag, const bool byID)
{
    if (byID) return gameObjects_.Find(std::stoi(string));
    else return gameObjects_.Find(string, byTag);
}

void LobbyScene::ChangeGameObjectOrder(const std::string& name, const std::string& newPos)
{}

void LobbyScene::ChangeScene(const std::string& sceneName)
{
    transitionTo_ = sceneName;
}

void LobbyScene::End()
{
    delete map_;
    gameObjects_.Clear();
    game_->GetTransitionManager()->Clear();
    pm_.Clear();
}